load("@rules_cc//cc:defs.bzl", "cc_library")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "args_parser",
    srcs = ["src/args_parser.cpp"],
    hdrs = ["include/args_parser.hpp", "include/args_exception.hpp"],
    strip_include_prefix = "include",
)

cc_test(
  name = "args_parser_tests",
  size = "small",
  srcs = ["test/args_parser.cpp"],
  deps = [
      "@com_google_googletest//:gtest_main",
      ":args_parser"
      ],
)
