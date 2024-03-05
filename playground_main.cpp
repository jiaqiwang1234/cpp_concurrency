#include <iostream>
#include <thread>
#include <future>
#include <chrono>
void play() {
  std::cout << "Start to execute play\n";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "Execution ends\n";
}


int main() {
  std::promise<int> p;
  std::thread internal_thread = std::thread([&p]{
    p.set_value(15);
    play();
  });
  auto flag = p.get_future().get();
  if (flag) {
    throw ;
  }
  internal_thread.join();
  return 0;
}
