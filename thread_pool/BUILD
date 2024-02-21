load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "simple_thread_pool",
    hdrs = ["simple_thread_pool.h"],
    deps = [
        "//threadsafe_queue:waitable_fine_grained_threadsafe_queue",
        "//:joining_thread",
    ]
)