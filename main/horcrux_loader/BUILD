load("@rules_cc//cc:defs.bzl", "cc_library")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "abstract_horcrux_loader",
    hdrs = ["include/abstract_horcrux_loader.hpp"],
    strip_include_prefix = "include",
)

cc_library(
    name = "horcrux_loader",
    srcs = ["src/horcrux_loader.cpp"],
    hdrs = ["include/horcrux_loader.hpp"],
    strip_include_prefix = "include",
    deps = [":abstract_horcrux_loader"]
)