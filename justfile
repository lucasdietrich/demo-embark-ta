# Justfile for managing build tasks
# Use `just <task>` to run a specific task
# Use `just --summary` to see available tasks


builddir := "build"


exe := builddir + "/libmyta.so"


# Setup, runs only if builddir or ninja file is missing
setup:
  if [ ! -f {{builddir}}/build.ninja ]; then \
    meson {{builddir}} --prefix=/usr; \
  fi

reconfigure:
    meson setup {{builddir}} --reconfigure

build: setup ta && rust-build
	meson compile -C {{builddir}}


install: build
    DESTDIR=./sysroot meson install -C {{builddir}}


_ensure-sdk-env:
    @if [ -z "${SDKTARGETSYSROOT:-}" ]; then \
        echo "Warning: SDKTARGETSYSROOT is not set. Source a Yocto SDK environment first, for example: source /opt/amy/1.0/environment-setup-*"; \
        exit 1; \
    fi

install-sdk-legacy: _ensure-sdk-env install
    sudo cp -vR build/./sysroot/* "$SDKTARGETSYSROOT"

install-sdk: _ensure-sdk-env
    sudo env "PATH=$PATH" "DESTDIR=$SDKTARGETSYSROOT" "$(command -v meson)" install -C {{builddir}}


clean:
    rm -rf {{builddir}}

# OP-TEE
ta_dir := builddir + "/ta"

# Build and sign the Trusted Application with the TA dev kit (source .env first)
ta:
    make -C ta O={{join(justfile_directory(), ta_dir)}}

ta_install_path := "/lib/optee_armtz"

# Install the signed TA where tee-supplicant loads it from
ta-deploy: ta
    ssh {{target}} 'mkdir -p {{ta_install_path}}'
    scp {{ta_dir}}/*.ta {{target}}:{{ta_install_path}}/

# Start tee-supplicant on the target if it is not running
tee-supplicant:
    ssh {{target}} 'pidof tee-supplicant >/dev/null || tee-supplicant -d'

deploy-demo: build
    scp {{builddir}}/myta-demo {{target}}:~/

# Run the demo application on the target
run-target *args: deploy tee-supplicant
    ssh {{target}} 'LD_LIBRARY_PATH=~ ~/myta-demo {{args}}'
# Rust wrapper of the C library
rust_dir := "rust"
rust_target := "aarch64-poky-linux-gnu"
rust_examples := rust_dir + "/target/" + rust_target + "/debug/examples"

# Build the Rust wrapper and its example, the C library must have been built (`just build`)
rust-build:
    cd {{rust_dir}} && MYTA_LIB_DIR={{justfile_directory()}}/{{builddir}} cargo build --examples

rust-clean:
    cd {{rust_dir}} && cargo clean

# Copy the Rust example to the target, the C library is copied by `deploy`
rust-deploy: rust-build
    scp {{rust_examples}}/demo {{target}}:~/myta-rust-demo

# Run the Rust example on the target
rust-run-target *args: deploy tee-supplicant
    ssh {{target}} '~/myta-rust-demo {{args}}'
# QEMU
qemu *args: build
  ./scripts/run-qemu.sh {{exe}} {{args}}
qemu-debug *args: build
  ./scripts/run-qemu.sh --debug {{exe}} {{args}}

disassemble: build
  scripts/disassemble.sh {{exe}}
format:
    ./scripts/do-clang-format.sh
    cd rust && cargo fmt


target := "mpx"

deploy: build rust-deploy ta-deploy deploy-demo
  scp {{exe}} {{target}}:~/
