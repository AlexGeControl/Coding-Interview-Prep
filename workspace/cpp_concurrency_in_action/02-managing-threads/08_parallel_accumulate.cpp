#include <iostream>

#include <numeric>

#include <vector>

#include <thread>

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator begin, Iterator end, T &result) {
        result = std::accumulate(begin, end, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T init) {
    const size_t N = std::distance(begin, end);

    // determine the number of threads for parallel accumulation:
    const size_t min_per_thread = 10;
    const size_t min_num_threads = (N + min_per_thread - 1) / min_per_thread;

    const size_t num_hardware_threads = std::thread::hardware_concurrency();
    const size_t max_hardware_threads = (0 == num_hardware_threads ? 2 : num_hardware_threads);

    const size_t num_threads = std::min(max_hardware_threads, min_num_threads);

    // calculate:
    const size_t block_size = N / num_threads;

    std::vector<T> partial_results(num_threads, init);
    std::vector<std::thread> workers;

    Iterator block_start = begin;
    for (size_t i = 0; i < num_threads - 1; ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        workers.emplace_back( accumulate_block<Iterator, T>(), block_start, block_end, std::ref( partial_results.at(i) ) );

        block_start = block_end;        
    }

    partial_results.at(num_threads - 1) = std::accumulate(block_start, end, init);

    for (auto &worker: workers) worker.join();

    // summary:
    std::cout << "\t threads required: " << min_num_threads << std::endl
              << "\t threads available: " << max_hardware_threads << std::endl
              << "threads allocated: " << num_threads << std::endl
              << "parallel block size: " << block_size << std::endl
              << "main thread block size: " << std::distance(block_start, end) << std::endl
              << std::endl;

    return std::accumulate(partial_results.begin(), partial_results.end(), init);
}

int main() {
    const size_t N = 200;

    std::vector<int> data;
    for (size_t i = 0; i < N; ++i) data.push_back(i);

    std::cout << parallel_accumulate<std::vector<int>::iterator, int>(data.begin(), data.end(), 0) << std::endl;

    return EXIT_SUCCESS;
}