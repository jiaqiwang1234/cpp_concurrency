//
// Created by George Wang on 1/21/24.
//

#ifndef CPP_CONCURRENCY_MUTEXTESTS_H
#define CPP_CONCURRENCY_MUTEXTESTS_H

#include <mutex>
namespace wjiaqi {
namespace cppconcurrency {
class MutexTests {
private:
    void ModifyValue(int thread_id);
    void ModifyValueWithAllLocks(int thread_id);
    std::mutex m;
    std::mutex m1;
    int shared_value = 1;
public:
    void Test();
};
}  // namespace cppconcurrency
}  // namespace wjiaqi

#endif //CPP_CONCURRENCY_MUTEXTESTS_H
