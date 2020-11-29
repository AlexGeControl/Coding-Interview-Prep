#include <iostream>

#include <cstdlib>

#include <thread>

struct Func {
    int N_;

    Func(const int N) : N_(N) {}

    void operator() (void) {
        std::cout << "I am functor " << N_ << std::endl;
    }
};

class scoped_thread {
public:
    explicit scoped_thread(std::thread t) : t_(std::move(t)) {
        if ( !t_.joinable() ) throw std::logic_error("Not joinable thread");
    }
    ~scoped_thread() {
        t_.join();
    }
    scoped_thread(scoped_thread const &)=delete;
    scoped_thread &operator()(scoped_thread const &)=delete;
private:
    std::thread t_;
};

int main() {
    scoped_thread s{ std::thread(Func(42)) };

    return EXIT_SUCCESS;
}