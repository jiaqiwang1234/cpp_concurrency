#include <functional>
#include <thread>

#include "/joining_thread.h"
#include "/threadsafe_queue/waitable_fine_grained_threadsafe_queue.h"

namespace cppconcurrency {
namespace thread_pool {
class thread_pool {
  std::atomic_bool done_;
  threadsafequeue::threadsafe_queue<std::function<void()>> work_queue_;
  std::vector<std::thread> threads_;
  joiningthread::joining_thread joiner_;
  void worker_thread() {
    while (!done_) {
      std::function<void()> task;
      if (work_queue_.try_pop(task)) {
        task();
      } else {
        std::this_thread::yield();
      }
    }
  }

 public:
  thread_pool() : done_(false), joiner_(threads_) {
    uint16_t const thread_count = std::thread::hardware_concurrency();
    for (uint16_t i = 0; i < thread_count; ++i) {
      threads_.push_back(std::thread(&thread_pool::worker_thread, this));
    }
  }

  ~thread_pool() { done_ = true; }

  template <typename FunctionType>
  void submit(FunctionType f) {
    work_queue_.push(std::function<void()>(f));
  }
}
}  // namespace thread_pool
}  // namespace cppconcurrency
