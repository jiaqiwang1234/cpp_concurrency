#include <functional>
#include <thread>

#include "../joining_thread.h"
#include "../threadsafe_queue/waitable_fine_grained_threadsafe_queue.h"

namespace cppconcurrency {
namespace thread_pool {

class thread_pool {
  std::atomic_bool done_;
  ::cppconcurrency::threadsafequeue::threadsafe_queue<std::function<void()>> work_queue_;
  std::vector<::cppconcurrency::joiningthread::joining_thread> threads_;
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
   explicit thread_pool(const uint16_t thread_count): done_(false) {
     for (uint16_t i = 0; i < thread_count; ++i) {
       ::cppconcurrency::joiningthread::joining_thread joining_thread(&thread_pool::worker_thread, this);
       threads_.emplace_back(std::move(joining_thread));
     }
   }
  thread_pool(): thread_pool(std::thread::hardware_concurrency()) {}

  ~thread_pool() { done_ = true; }

  template <typename FunctionType>
  void submit(FunctionType f) {
    work_queue_.push(std::function<void()>(f));
  }
};

}  // namespace thread_pool
}  // namespace cppconcurrency
