#include <iostream>

#include <vector>

#include <thread>

struct Reducer {
    void operator() (const int val, int &result) {
        result += val * val;
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
    int result = 0;

    const int N = 10;

    std::vector<std::thread> reducers;
    for (int i = 1; i < N; ++i) {
        reducers.emplace_back( Reducer(), i, std::ref(result) );
    }

    for (auto &reducer: reducers) {
        reducer.join();
    }

    std::cout << "The result should equal to 285: " << ( 285 == result ? "true" : "false" ) << std::endl;

    return EXIT_SUCCESS;
}