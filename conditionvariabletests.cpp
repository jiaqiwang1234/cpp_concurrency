//
// Created by George Wang on 1/21/24.
//

#include "conditionvariabletests.h"
#include <iostream>
#include <thread>

namespace wjiaqi{
namespace cppconcurrency{
void ConditionVariableTests::Consume(int32_t consumer_id) {
    while (true) {
        std::cout << "Now Consumer " << consumer_id << " is consuming the messages\n";
        std::unique_lock unique_lck {lock};
        condition_variable.wait(unique_lck, [this]{return !message_queue.empty();});
        auto id = message_queue.front();
        std::cout << "Currently the first message is " << id << "\n";
        message_queue.pop();
        unique_lck.unlock();
    }
}
void ConditionVariableTests::Produce(int32_t producer_id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock lck {lock};
        std::cout << "Producer " << producer_id << " is working.\n";
        message_queue.push(producer_id * 10 + i);
        condition_variable.notify_all();
        lck.unlock();
    }

}

void ConditionVariableTests::Test() {
    std::cout << "Start to test the ConditionVariable\n";

    std::thread consumer1 {&ConditionVariableTests::Consume, this, 1};
    std::thread consumer2 {&ConditionVariableTests::Consume, this, 2};
    std::thread producer1 {&ConditionVariableTests::Produce, this, 1};
    std::thread producer2 {&ConditionVariableTests::Produce, this, 2};

    consumer1.join();
    consumer2.join();
    producer1.join();
    producer2.join();
}
}  // namespace cppconcurrency
}  // namespace wjiaqi