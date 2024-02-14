#ifndef CPP_CONCURRENCY__JOINING_THREAD_H_
#define CPP_CONCURRENCY__JOINING_THREAD_H_

#include <thread>

class JoiningThread {
  // See C++ Concurrency In Action 2nd Edition P29 Listing 2.7
  std::thread t_;
public:
  JoiningThread() noexcept = default;
  template <typename Callable, typename ... Args>

  explicit JoiningThread(Callable&& func, Args&& ... args):
    t_(std::forward<Callable>(func), std::forward<Args>(args) ...) {}

  explicit JoiningThread(std::thread t) noexcept: t_(std::move(t)) {}

  JoiningThread(JoiningThread&& other) noexcept:
    t_(std::move(other.t_)) {}

  JoiningThread& operator=(JoiningThread&& other) noexcept {
    if(joinable()) {
      join();
    }
    t_ = std::move(other.t_);
    return *this;
  }

  JoiningThread& operator=(std::thread t) noexcept {
    if(joinable()) {
      join();
    }
    t_ = std::move(t);
    return *this;
  }

  ~JoiningThread() {
    if (joinable()) {
      join();
    }
  }

  void swap(JoiningThread& other) noexcept {
    t_.swap(other.t_);
  }

  [[nodiscard]] std::thread::id get_id() const noexcept {
    return t_.get_id();
  }

  [[nodiscard]] bool joinable() const noexcept {
    return t_.joinable();
  }

  void join() {
    t_.join();
  }

  void detach() {
    t_.detach();
  }

  [[nodiscard]] std::thread& as_thread() noexcept {
    return t_;
  }

  [[nodiscard]] const std::thread& as_thread() const noexcept {
    return t_;
  }
};

#endif // CPP_CONCURRENCY__JOINING_THREAD_H_
