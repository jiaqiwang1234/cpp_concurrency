#include <iostream>
#include <thread>
#include <algorithm>
#include <utility>
#include "mutextests.h"
#include "readwritelocktests.h"
#include "conditionvariabletests.h"
#include "packagedtasktests.h"

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
    wjiaqi::cppconcurrency::PackagedTaskTests packagedTaskTests;
    packagedTaskTests.Test();
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
