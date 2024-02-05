//
// Created by George Wang on 1/21/24.
//

#include <iostream>
#include <thread>
#include "readwritelocktests.h"
namespace wjiaqi {
namespace cppconcurrency{
void ReadWriteLockTests::Read(int thread_id) {
    std::shared_lock read_lock {read_write_lock};
    std::cout << "Thread " << thread_id << " reads output is " << shared_value << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void ReadWriteLockTests::Write(int thread_id) {
    std::unique_lock write_lock {read_write_lock};
    shared_value += 10;
    std::cout << "Thread " << thread_id << " write output is " << shared_value << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ReadWriteLockTests::Test() {
    std::cout << "Start with ReadWriteLockTests\n";
    std::thread t1 {&ReadWriteLockTests::Read, this, 1};
    std::thread t2 {&ReadWriteLockTests::Read, this, 2};
    std::thread t3 {&ReadWriteLockTests::Read, this, 3};
    std::thread t4 {&ReadWriteLockTests::Write, this, 4};
    std::thread t5 {&ReadWriteLockTests::Read, this, 5};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
}  // namespace cppconcurrency
}  // namespace wjiaqi