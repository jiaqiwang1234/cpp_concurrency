load("@rules_cc//cc:defs.bzl", "cc_library")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "simple_threadsafe_queue",
    hdrs = ["simple_threadsafe_queue.h"],
)

cc_library(
    name = "fine_grained_locking_threadsafe_queue",
    hdrs = ["fine_grained_locking_threadsafe_queue.h"],
)

cc_library(
    name = "waitable_fine_grained_threadsafe_queue",
    hdrs = ["waitable_fine_grained_threadsafe_queue.h"],
    srcs = ["waitable_fine_grained_threadsafe_queue.cpp"],
)