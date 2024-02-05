//
// Created by George Wang on 1/22/24.
//

#ifndef CPP_CONCURRENCY_PACKAGEDTASKTESTS_H
#define CPP_CONCURRENCY_PACKAGEDTASKTESTS_H

#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <queue>

namespace wjiaqi{
    namespace cppconcurrency{
class PackagedTaskTests {
public:
    void Test();
private:
    static double accum(int start, int end, double init);
};
    }  // namespace cppconcurrency
}  // namespace wjiaqi

#endif //CPP_CONCURRENCY_PACKAGEDTASKTESTS_H
