load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_foreign_cc//foreign_cc:configure.bzl", "configure_make")

package(
    default_visibility = ["//visibility:public"],
)

config_setting(
  name = "windows_build",
  values = {
    "define": "windows_build=true"
  }
)

configure_make(
    name = "openssl",
    configure_command = select({
        ":windows_build" : "Configure",
        "//conditions:default": "config",
    }),
    configure_options = select({
        ":windows_build" : ["mingw64", "no-shared"],
        "//conditions:default": ["no-shared"],
    }),
    lib_source = "@openssl//:all",
    out_static_libs = [
        "libssl.a",
        "libcrypto.a",
    ],
)

cc_binary(
    name = "horcrux",
    srcs = ["main.cpp"],
    deps = [
            ":openssl"
        ],
    linkopts = [
        "-lpthread",
        "-ldl",
    ]
)