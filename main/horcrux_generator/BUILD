load("@rules_cc//cc:defs.bzl", "cc_library")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "abstract_horcrux_generator",
    hdrs = ["include/abstract_horcrux_generator.hpp"],
    strip_include_prefix = "include",
)

cc_library(
    name = "horcrux_generator",
    srcs = ["src/horcrux_generator.cpp"],
    hdrs = [
        "include/horcrux_generator.hpp",
        "include/horcrux_generate_exception.hpp"
        ],
    strip_include_prefix = "include",
    deps = [
        ":abstract_horcrux_generator",
        "//main:openssl",
        "//main/utils:constants"
    ]
)