//! Links the shared C library `lib<crate name>.so`.
//!
//! Generic: copy it as is next to the manifest of a crate named after the C
//! library it wraps.
//!
//! The library is searched in `<CRATE>_LIB_DIR` if set (the crate name
//! uppercased with `-` replaced by `_`), otherwise in the default directories of
//! the linker (e.g. the SDK sysroot).

use std::env;

fn main() {
    let name = env::var("CARGO_PKG_NAME").unwrap();
    let lib_dir_env = format!("{}_LIB_DIR", name.to_uppercase().replace('-', "_"));

    println!("cargo:rerun-if-env-changed={lib_dir_env}");
    if let Ok(dir) = env::var(&lib_dir_env) {
        println!("cargo:rerun-if-changed={dir}/lib{name}.so");
        println!("cargo:rustc-link-search=native={dir}");
    }
    println!("cargo:rustc-link-lib=dylib={name}");
    // Once deployed, the binaries find the library next to them
    println!("cargo:rustc-link-arg=-Wl,-rpath,$ORIGIN");
}
