load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "simple_thread_pool",
    hdrs = ["simple_thread_pool.h"],
    deps = [
        "//threadsafe_queue:waitable_fine_grained_threadsafe_queue",
        "//:joining_thread",
    ]
)

cc_library(
    name = "function_wrapper",
    hdrs = ["function_wrapper.h"],
    deps = []
)

cc_library(
    name = "waitable_task_thread_pool",
    hdrs = ["waitable_task_thread_pool.h"],
    deps = [
        ":function_wrapper",
         "//threadsafe_queue:waitable_fine_grained_threadsafe_queue",
        "//:joining_thread",
    ]
)