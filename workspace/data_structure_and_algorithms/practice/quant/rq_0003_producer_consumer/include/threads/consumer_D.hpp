/*
 * @Description: consumer D implementation
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_THREAD_CONSUMER_D_HPP
#define PRODUCER_CONSUMER_THREAD_CONSUMER_D_HPP

#include <iostream>
#include <iomanip>

#include <thread>
#include <chrono>

#include "data/data.hpp"
#include "queue/lock_based_queue.hpp"

#include <atomic>

class ConsumerD {
public:
    ConsumerD() {}

    void operator()(const std::atomic<bool> &is_available, const std::atomic<int32_t> &real_time_sum) {
        // wait until real-time sum is initialized:
        while ( !is_available.load(std::memory_order_acquire) ) ;

        // get init time:
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << std::fixed << std::setprecision(2);

        while (true) {
            int32_t sum = real_time_sum.load(std::memory_order_acquire);

            // display real-time sum:
            auto curr = std::chrono::high_resolution_clock::now();

            int32_t integral = sum / 100;
            int32_t fractional = std::abs(sum) % 100;

            std::cout << "Real-Time Sum @ " << std::chrono::duration<double, std::ratio<60, 1>>(curr - start).count()
                      << ": " << integral << "." << fractional << std::endl;

            // yield:
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};

#endif