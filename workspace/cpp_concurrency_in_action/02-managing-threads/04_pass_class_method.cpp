#include <iostream>

#include <cstdlib>

#include <vector>

#include <thread>

class Generator {
public:
    Generator(const int N, const int M) : N_(N), M_(M) {}

    void Generate(std::vector<int> &output) {
        for (int i = 0; i < N_; ++i) {
            output.push_back( rand() % M_ );
        }
    }
private:
    int N_;
    int M_;
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
    Generator generator(4, 10);
    std::vector<int> data;
    std::thread t{ &Generator::Generate, &generator, std::ref(data) };
    t.join();
    
    std::cout << "Data generated: " << std::endl;
    for (const int &d: data) {
        std::cout << d << " " << std::endl;
    }

    return EXIT_SUCCESS;
}