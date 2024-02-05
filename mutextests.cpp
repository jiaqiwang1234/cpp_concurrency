//
// Created by George Wang on 1/21/24.
//

#include "mutextests.h"

#include <iostream>
#include <thread>
#include <chrono>

namespace wjiaqi{
namespace cppconcurrency{
using namespace std::chrono_literals;

void MutexTests::Test() {
    std::cout << "Start to modify the shared value\n";
    std::thread thread1 {&MutexTests::ModifyValueWithAllLocks, this, 1};
    std::thread thread2 {&MutexTests::ModifyValueWithAllLocks, this, 2};
    std::thread thread3 {&MutexTests::ModifyValueWithAllLocks, this, 3};
    std::thread thread4 {&MutexTests::ModifyValueWithAllLocks, this, 4};

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

}

void MutexTests::ModifyValue(int thread_id) {
    std::scoped_lock lck(m);
    std::cout << "Got the lock for thread" << thread_id <<"\n";
    shared_value += 7;
    std::this_thread::sleep_for(1s);
    std::cout << "Value is " << shared_value << "\n";
}

void MutexTests::ModifyValueWithAllLocks(int thread_id) {
    std::scoped_lock lck {m, m1};
    std::cout << "Got the lock m and m1 for thread" << thread_id <<"\n";
    shared_value += 7;
    std::this_thread::sleep_for(1s);
    std::cout << "Value is " << shared_value << "\n";
}
}  // namespace cppconcurrency
}  // namespace wjiaqi
