#include <iostream>

#include <cstdlib>

#include <vector>

#include <thread>

struct Func {
    const int N_;
    const int M_;
    Func(const int N, const int M) : N_(N), M_(M) {}

    void operator() (std::vector<int> &output) {
        output.clear();

        for (int i = 0; i < N_; ++i) {
            output.push_back( rand() % M_ );
        }
    }
};

class thread_guard {
public:
    explicit thread_guard(std::thread &t) : t_(t) {}
    ~thread_guard() {
        if (t_.joinable()) {
            t_.join();
        }
    }
    thread_guard(thread_guard const &)=delete;
    thread_guard &operator()(thread_guard const &)=delete;
private:
    std::thread &t_;
};

int main() {
    std::vector<int> data;
    std::thread t{ Func(3, 10), std::ref(data) };
    t.join();
    
    std::cout << "Data generated: " << std::endl;
    for (const int &d: data) {
        std::cout << d << " " << std::endl;
    }

    return EXIT_SUCCESS;
}