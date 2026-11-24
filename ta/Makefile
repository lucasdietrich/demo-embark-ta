# OP-TEE Trusted Application, built and signed with the OP-TEE TA dev kit.
#
# Built by `just ta`, TA_DEV_KIT_DIR and CROSS_COMPILE come from the
# environment (source .env). It can also be run by hand:
#
#   make TA_DEV_KIT_DIR=<export-ta_arm64> CROSS_COMPILE=aarch64-linux-gnu- O=out

# The UUID of the Trusted Application, it names the signed binary (<uuid>.ta).
# It must match the UUID of ta/include/myta_ta.h.
BINARY = c081257b-243b-581e-8cc2-a3895ee16564

# The flags of the Yocto SDK environment target Linux userspace, not TAs: drop
# them, only keep the sysroot so that gcc finds libgcc.
override CFLAGS := $(if $(SDKTARGETSYSROOT),--sysroot=$(SDKTARGETSYSROOT))
override CPPFLAGS :=
override CXXFLAGS :=
override LDFLAGS :=
unexport OPENSSL_CONF OPENSSL_MODULES

include $(TA_DEV_KIT_DIR)/mk/ta_dev_kit.mk
