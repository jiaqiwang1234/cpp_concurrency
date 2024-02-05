//
// Created by George Wang on 1/21/24.
//

#ifndef CPP_CONCURRENCY_READWRITELOCKTESTS_H
#define CPP_CONCURRENCY_READWRITELOCKTESTS_H

#include <shared_mutex>
namespace wjiaqi {
namespace cppconcurrency{
class ReadWriteLockTests {
public:
    void Test();
private:
    std::shared_mutex read_write_lock;
    int shared_value = 1;
    void Read(int thread_id);
    void Write(int thread_id);
};

}  // namespace cppconcurrency
}  // namespace wjiaqi


#endif //CPP_CONCURRENCY_READWRITELOCKTESTS_H
