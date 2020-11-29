#include <iostream>

#include <string>

#include <thread>

struct Func {
    const std::string &greeting_;

    Func(const std::string &greeting) : greeting_(greeting) {}

    void operator() () {
        std::cout << greeting_ << std::endl;
    }
};

class thread_guard {
public:
    explicit thread_guard(std::thread &t) : t_(t) {}
    ~thread_guard() {
        if (t_.joinable()) {
            t_.join();
            std::cout << "The guarded thread has been properly joined." << std::endl;
        }
    }
    thread_guard(thread_guard const &)=delete;
    thread_guard &operator()(thread_guard const &)=delete;
private:
    std::thread &t_;
};

int main() {
    std::string greeting = "Hello, CPP concurrency!";
    
    std::thread t{ Func(greeting) };
    thread_guard g(t);

    return EXIT_SUCCESS;
}