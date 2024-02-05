//
// Created by George Wang on 1/21/24.
//

#ifndef CPP_CONCURRENCY_CONDITIONVARIABLETESTS_H
#define CPP_CONCURRENCY_CONDITIONVARIABLETESTS_H
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <queue>

namespace wjiaqi{
namespace cppconcurrency{

class ConditionVariableTests {
public:
    void Test();
private:
    void Produce(int32_t producer_id);
    void Consume(int32_t consumer_id);
    std::mutex lock;
    std::condition_variable condition_variable;
    std::queue<int32_t> message_queue;
};
}  // namespace cppconcurrency
}  // namespace wjiaqi

#endif //CPP_CONCURRENCY_CONDITIONVARIABLETESTS_H
