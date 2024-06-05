#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <future>

static int solve(std::function<int()> func, const unsigned int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    return func();
}

static int theJobFunction(){
    std::cout << "function runs" << std::endl;
    return 0;
}

int main(int argc, char* argv[]){
    auto start = std::chrono::system_clock::now();
    // std::cout << "Start: " << start.time_since_epoch().count() << "\n";
    auto result0 = std::async(std::launch::async, solve, &theJobFunction, 5000);
    // auto result = solve(&theJobFunction, 5000);
    // std::cout << "Result: " << result << "\n";
    std::cout << "Result0: " << result0.get() << "\n";
    std::chrono::duration<double, std::milli> elapsed{std::chrono::system_clock::now() - start};
    std::cout << "Elapsed: " << elapsed.count() << "ms\n";
    return 0;
}