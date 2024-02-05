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
        futuretests.h)
