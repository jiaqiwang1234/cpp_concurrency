#include "waitable_fine_grained_threadsafe_queue.h"

#include <thread>
#include <memory>

namespace cppconcurrency{
namespace threadsafequeue{

// Public methods

template<typename T>
void threadsafe_queue<T>::push(T new_value) {
    std::shared_ptr<T> new_data(
        std::make_shared<T>(std::move(new_value))
    );

    std::unique_ptr<node> p(new node);
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        node* const new_tail = p.get();
        tail->next = std::move(p);
        tail = new_tail;
    }
    data_cond.notify_one();
}

template<typename T>
std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop() {
    std::unique_ptr<node> const old_head = wait_pop_head();
    return old_head->data;
}

template<typename T>
void threadsafe_queue<T>::wait_and_pop(T& value) {
    std::unique_ptr<node> const old_head = wait_pop_head(value);
}

template<typename T>
std::shared_ptr<T> threadsafe_queue<T>::try_pop() {
    std::unique_ptr<node> old_head = try_pop_head();
    return old_head ? old_head->data : std::shared_ptr<T>();
}

template<typename T>
bool threadsafe_queue<T>::try_pop(T& value) {
    std::unique_ptr<node> old_head = try_pop_head();
    return old_head;
}

template<typename T>
bool threadsafe_queue<T>::empty() {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    return (head.get() == get_tail());
}
}  // namespace threadsafequeue
}  // namespace cppconcurrency
