#ifndef CPP_CONCURRENCY__JOINING_THREAD_H_
#define CPP_CONCURRENCY__JOINING_THREAD_H_

#include <thread>
namespace cppconcurrency {
namespace joiningthread {
class joining_thread {
  // See C++ Concurrency In Action 2nd Edition P29 Listing 2.7
  std::thread t_;

 public:
  joining_thread() noexcept = default;
  template <typename Callable, typename... Args>

  explicit joining_thread(Callable&& func, Args&&... args)
      : t_(std::forward<Callable>(func), std::forward<Args>(args)...) {}

  explicit joining_thread(std::thread t) noexcept : t_(std::move(t)) {}

  joining_thread(joining_thread&& other) noexcept : t_(std::move(other.t_)) {}

  joining_thread& operator=(joining_thread&& other) noexcept {
    if (joinable()) {
      join();
    }
    t_ = std::move(other.t_);
    return *this;
  }

  joining_thread& operator=(std::thread t) noexcept {
    if (joinable()) {
      join();
    }
    t_ = std::move(t);
    return *this;
  }

  ~joining_thread() {
    if (joinable()) {
      join();
    }
  }

  void swap(joining_thread& other) noexcept { t_.swap(other.t_); }

  [[nodiscard]] std::thread::id get_id() const noexcept { return t_.get_id(); }

  [[nodiscard]] bool joinable() const noexcept { return t_.joinable(); }

  void join() { t_.join(); }

  void detach() { t_.detach(); }

  [[nodiscard]] std::thread& as_thread() noexcept { return t_; }

  [[nodiscard]] const std::thread& as_thread() const noexcept { return t_; }
};
}  // namespace joiningthread
}  // namespace cppconcurrency

#endif  // CPP_CONCURRENCY__JOINING_THREAD_H_
