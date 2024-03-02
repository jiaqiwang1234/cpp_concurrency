#include <functional>
#include <thread>

#include "/joining_thread.h"
#include "/thread_pool/function_wrapper.h"
#include "/threadsafe_queue/waitable_fine_grained_threadsafe_queue.h"

namespace cppconcurrency {
namespace thread_pool {
class thread_pool {
  threadsafequeue::threadsafe_queue<function_wrapper> work_queue_;
  void worker_thread() {
    while (!done) {
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
        std::packaged_task<result_type()> task<std::move(f)>;
        std::future<result_type> res(task.get_future());
        work_queue_.push(std::move(task));
        return res;
      }
}
}  // namespace thread_pool
}  // namespace cppconcurrency
