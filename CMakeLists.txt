cmake_minimum_required(VERSION 3.27)
project(cpp_concurrency)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        cpp_concurrency main.cpp
        mutextests.cpp
        mutextests.h
        readwritelocktests.cpp
        readwritelocktests.h
        conditionvariabletests.cpp
        conditionvariabletests.h
        packagedtasktests.cpp
        packagedtasktests.h
        futuretests.cpp
        futuretests.h
        joining_thread.h
        thread_pool/waitable_task_thread_pool.h
        thread_pool/simple_thread_pool.h
        thread_pool/function_wrapper.h
        threadsafe_queue/fine_grained_locking_threadsafe_queue.h
        threadsafe_queue/simple_threadsafe_queue.h
        threadsafe_queue/waitable_fine_grained_threadsafe_queue.cpp
        playground_main.cpp
)
