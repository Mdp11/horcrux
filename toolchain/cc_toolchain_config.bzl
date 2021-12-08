load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

load(
   "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
   "feature",
   "flag_group",
   "flag_set",
   "tool_path",
   "artifact_name_pattern",
)

all_link_actions = [
   ACTION_NAMES.cpp_link_executable,
   ACTION_NAMES.cpp_link_dynamic_library,
   ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            path = "/usr/bin/x86_64-w64-mingw32-gcc",
        ),
        tool_path(
            name = "ld",
            path = "/usr/bin/x86_64-w64-mingw32-ld",
        ),
        tool_path(
            name = "ar",
            path = "/usr/bin/x86_64-w64-mingw32-ar",
        ),
        tool_path(
            name = "cpp",
            path = "/usr/bin/x86_64-w64-mingw32-cpp",
        ),
        tool_path(
            name = "gcov",
            path = "/usr/bin/x86_64-w64-mingw32-gcov",
        ),
        tool_path(
            name = "nm",
            path = "/usr/bin/x86_64-w64-mingw32-nm",
        ),
        tool_path(
            name = "objdump",
            path = "/usr/bin/x86_64-w64-mingw32-objdump",
        ),
        tool_path(
            name = "strip",
            path = "/usr/bin/x86_64-w64-mingw32-strip",
        ),
        tool_path(
            name = "windres",
            path = "/usr/bin/x86_64-w64-mingw32-windres",
        ),
    ]

    features = [
       feature(
           name = "default_linker_flags",
           enabled = True,
           flag_sets = [
               flag_set(
                   actions = all_link_actions,
                   flag_groups = ([
                       flag_group(
                           flags = [
                               "-static",
                               "-lstdc++",
                           ],
                       ),
                   ]),
               ),
           ],
       ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "/usr/x86_64-w64-mingw32/include",
            "/usr/lib/gcc/x86_64-w64-mingw32/9.3-win32/include/c++",
            "/usr/share/mingw-w64/include",
            "/usr/lib/gcc/x86_64-w64-mingw32/9.3-win32/include",
            "/usr/lib/gcc/x86_64-w64-mingw32/9.3-win32/include-fixed",
            "/usr/include",
        ],
        toolchain_identifier = "mingw_toolchain",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "x86_64-w64-mingw32-gcc ",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
        artifact_name_patterns = [
            artifact_name_pattern(
                category_name = "executable",
                prefix = "",
                extension = ".exe",
            ),
        ]
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)