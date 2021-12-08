load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip"],
  strip_prefix = "googletest-e2239ee6043f73722e7aa812a459f54a28552929",
)

all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

http_archive(
    name = "openssl",
    build_file_content = all_content,
    sha256 = "0b7a3e5e59c34827fe0c3a74b7ec8baef302b98fa80088d7f9153aa16fa76bd1",
    strip_prefix = "openssl-1.1.1l",
    urls = ["https://www.openssl.org/source/openssl-1.1.1l.tar.gz"],
)

http_archive(
    name = "rules_foreign_cc",
    sha256 = "47ed966580c11420191352e0bffdf1676b479c54c6f5b7656ab1dc75f22b2f76",
    strip_prefix = "rules_foreign_cc-605a80355dae9e1855634b733b98a5d97a92f385",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/605a80355dae9e1855634b733b98a5d97a92f385.zip",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()