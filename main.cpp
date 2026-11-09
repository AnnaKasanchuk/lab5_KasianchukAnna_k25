// Author: Kasianchuk Anna K-25
// Variant 16
// Compiler: Bundled MinGW 14.0 w64 (GCC 14), CLion toolchain
// Language standard: C++20

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <syncstream>

void compute(const std::string& name, int duration_seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(duration_seconds));
    std::osyncstream(std::cout) << name << std::endl;
}

void slow(const std::string& name) {
    compute(name, 7);
}

void quick(const std::string& name) {
    compute(name, 1);
}

void work() {
    auto start_time = std::chrono::steady_clock::now();

    auto future_C = std::async(std::launch::async, []() {
        slow("C");
    });

    auto future_quick = std::async(std::launch::async, []() {
        quick("B");
        quick("D2");
        quick("F2");
    });

    slow("A");

    future_C.get();
    future_quick.get();

    quick("D1");
    quick("F1");

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    std::osyncstream(std::cout) << "Elapsed time: " << elapsed << " s" << std::endl;
    std::osyncstream(std::cout) << "Work is done!" << std::endl;
}

int main() {
    work();
    return 0;
}