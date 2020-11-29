#include <iostream>

#include <numeric>

#include <vector>

#include <unordered_map>

#include <thread>

struct Mapper {
    void operator() (const int x, int &result, std::unordered_map<std::thread::id, int> &thread_monitor) {
        result = x * x;

        //
        // this is undefined behavior:
        //
        // thread_monitor[std::this_thread::get_id()] = result;
    }
};

int main() {
    const size_t N = 10;

    std::vector<int> data;
    for (size_t i = 1; i <= N; ++i) data.push_back(i);

    std::vector<int> partial_results(data.size());
    std::vector<std::thread> workers;
    std::unordered_map<std::thread::id, int> thread_monitor;
    for (size_t i = 0; i < data.size(); ++i) {
        workers.emplace_back( Mapper(), data.at(i), std::ref( partial_results.at(i) ) , std::ref(thread_monitor) );
    }

    for (auto &worker: workers) worker.join();

    int result = std::accumulate(partial_results.begin(), partial_results.end(), 0);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Worker Summary: " << std::endl;
    for (const auto &thread_summary: thread_monitor) {
        std::cout << "\t" << thread_summary.first << ": " << thread_summary.second << std::endl;
    }

    return EXIT_SUCCESS;
}