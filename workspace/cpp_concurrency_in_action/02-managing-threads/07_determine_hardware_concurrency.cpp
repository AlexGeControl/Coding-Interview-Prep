#include <iostream>

#include <thread>

int main() {
    std::cout << "Max hardware concurrency: " << std::thread::hardware_concurrency() << std::endl;
    
    return EXIT_SUCCESS;
}