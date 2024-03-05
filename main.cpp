#include <iostream>
#include <thread>
#include <algorithm>
#include <utility>
#include "mutextests.h"
#include "readwritelocktests.h"
#include "conditionvariabletests.h"
#include "packagedtasktests.h"
class NewThreadInvocation {
public:
    void Process(int i) {
        std::cout << "Start to process " << i << " on " << std::this_thread::get_id() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Process of " << i << " done\n";
    }
    void CreateNewThread(int i) {
        std::cout << "Creating a new thread for " << i << " on " << this << "\n";
        std::thread t(&NewThreadInvocation::Process, this, i);
        t.join();
        std::cout << i << " is joined\n";
    }
};

void f0();
void f(std::vector<double> v);
void fRef(std::vector<double> v);
struct FRef {
    std::vector<double>& v;
    explicit FRef(std::vector<double>& vv): v(vv) {}
    void operator()() {
        std::cout << "FRef's vector address is " << &v << "\n";
    }
};

struct F {
    std::vector<double> v;
    explicit F(std::vector<double> vv): v(std::move(vv)) {}
    void operator()() {
        std::cout << "F's vector address is " << &v << "\n";
    }
};

int main() {
//    wjiaqi::cppconcurrency::PackagedTaskTests packagedTaskTests;
//    packagedTaskTests.Test();
    NewThreadInvocation newThreadInvocation;
    newThreadInvocation.CreateNewThread(1);
    newThreadInvocation.CreateNewThread(2);
    return 0;
}

void f0 () {
    std::cout << "No argument input\n";
}
void f(std::vector<double> v) {
    std::cout << "f's vector address is " << &v << "\n";
}

void fRef(std::vector<double> v) {
    std::cout << "fRef's vector address is " << &v << "\n";
}
