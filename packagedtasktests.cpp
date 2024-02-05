//
// Created by George Wang on 1/22/24.
//

#include "packagedtasktests.h"

#include <iostream>
#include <thread>
#include <future>


namespace wjiaqi{
namespace cppconcurrency{
double PackagedTaskTests::accum(int start, int end, double init) {
    double ans = init;
    for (int i = start; i < end; ++i) {
        ans += i;
    }
    return ans;
}

void PackagedTaskTests::Test() {
    using TASK_TYPE = double(int, int, double);
    std::packaged_task<TASK_TYPE> pt0 {accum};
    std::packaged_task<TASK_TYPE> pt1 {accum};

    std::future<double> res0 = pt0.get_future();
    std::future<double> res1 = pt1.get_future();

    std::thread thread_pt0 {std::move(pt0), 1, 5, 0.5};
    std::thread thread_pt1 {std::move(pt1), 1, 10, 0.0};

    thread_pt0.join();
    thread_pt1.join();

    std::cout << res0.get() << " " << res1.get() << "\n";
}
}  // namespace cppconcurrency
}  // namespace wjiaqi