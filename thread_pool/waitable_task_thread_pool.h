
#include <functional>
#include <thread>
#include <future>

#include "../joining_thread.h"
#include "function_wrapper.h"
#include "../threadsafe_queue/waitable_fine_grained_threadsafe_queue.h"

namespace cppconcurrency {
namespace thread_pool {
class thread_pool {
private:
  std::atomic_bool done_;
  std::vector<::cppconcurrency::joiningthread::joining_thread> threads_;
  ::cppconcurrency::threadsafequeue::threadsafe_queue<function_wrapper> work_queue_;
  void worker_thread() {
    while (!done_) {
      function_wrapper task;
      if (work_queue_.try_pop(task)) {
        task();
      } else {
        std::this_thread::yield();
      }
    }
  }

 public:
  template <typename FunctionType>
  std::future<typename std::result_of<FunctionType()>::type> submit(
      FunctionType f) {
    typedef typename std::result_of<FunctionType()>::type result_type;
    std::packaged_task<result_type()> task(std::move(f));
    std::future<result_type> res(task.get_future());
    work_queue_.push(std::move(task));

    return res;
  }

  explicit thread_pool(const uint16_t thread_count): done_(false) {
    for (uint16_t i = 0; i < thread_count; ++i) {
      ::cppconcurrency::joiningthread::joining_thread joining_thread(&thread_pool::worker_thread, this);
      threads_.emplace_back(std::move(joining_thread));
    }
  }
  thread_pool(): thread_pool(std::thread::hardware_concurrency()) {}

  ~thread_pool() { done_ = true; }

  void run_pending_task() {
    function_wrapper task;
    if (work_queue_.try_pop(task)) {
      task();
    } else {
      std::this_thread::yield();
    }
  }
};
}  // namespace thread_pool
}  // namespace cppconcurrency
