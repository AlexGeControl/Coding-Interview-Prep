#include <iostream>

#include <thread>

void func(void) {
    std::cout << "Hello, CPP concurrency!" << std::endl;
}

int main() {
    std::thread t{func};
    // make the decision before the thread object is destroyed:
    t.join();

    return EXIT_SUCCESS;
}