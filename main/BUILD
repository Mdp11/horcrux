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
        ":windows_build" : ["mingw64", "no-shared", "RC=/usr/bin/x86_64-w64-mingw32-windres", "-I/usr/x86_64-w64-mingw32/include"],
        "//conditions:default": ["no-shared"],
    }),
    lib_source = "@openssl//:all",
    out_static_libs = [
        "libssl.a",
        "libcrypto.a",
    ],
)

cc_binary(
    name = "horcrux_main",
    srcs = ["main.cpp"],
    deps = [
            "//main/args_parser",
            "//main/horcrux_generator",
            "//main/horcrux_loader",
            ":openssl"
        ],
    linkopts = select({
           ":windows_build" : ["-lpthread", "-lwsock32", "-lcrypt32", "-lws2_32"],
           "//conditions:default": ["-lpthread", "-ldl"],
       }),
)
