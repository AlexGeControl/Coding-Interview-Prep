#include <iostream>

#include <string>

#include <thread>

struct Func {
    std::string greeting_;

    Func(const std::string &greeting) : greeting_(greeting) {}

    void operator() () {
        std::cout << greeting_ << std::endl;
    }
};

int main() {
    std::string greeting = "Hello, CPP concurrency!";

    std::thread t1{ Func(greeting + " 1") };
    std::thread t2{ Func(greeting + " 2") };

    t1.join();
    t2.join();
    
    return EXIT_SUCCESS;
}