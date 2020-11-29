#include <iostream>

#include <string>

#include <thread>

int main() {
    std::string greeting = "Hello, CPP concurrency!";

    std::thread t{
        [greeting] () {
            std::cout << greeting << std::endl;
        }
    };

    t.join();
    
    return EXIT_SUCCESS;
}