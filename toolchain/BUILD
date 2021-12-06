load(":cc_toolchain_config.bzl", "cc_toolchain_config")

package(default_visibility = ["//visibility:public"])

cc_toolchain_suite(
    name = "mingw_suite",
    toolchains = {
        "k8": ":mingw_toolchain",
    },
)

filegroup(name = "empty")

cc_toolchain(
    name = "mingw_toolchain",
    toolchain_identifier = "mingw-toolchain",
    toolchain_config = ":mingw_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)

cc_toolchain_config(name = "mingw_toolchain_config")