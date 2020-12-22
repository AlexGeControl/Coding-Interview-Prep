/*
 * @Description: producer B implementation
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_THREAD_PRODUCER_B_HPP
#define PRODUCER_CONSUMER_THREAD_PRODUCER_B_HPP

#include <iostream>
#include <iomanip>

#include <random>

#include <thread>
#include <chrono>

#include <memory>

#include "data/B.hpp"

#include "data/data.hpp"
#include "queue/lock_based_queue.hpp"

class ProducerB {
public:
    ProducerB(const int N_, const double lo_, const double hi_) : N(N_), lo(lo_), hi(hi_) {}

    void operator()(LockBasedQueue<Data> &queue) {
        // init random float generator:
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_real_distribution<double> uniform_dist(lo, hi);
        
        // init container:
        std::unique_ptr<double[]> data(new double[N]);
        
        while (true) {
            // generate N random float between 0.0 and 1.0:
            for (int i = 0; i < N; ++i) {
                data.get()[i] = uniform_dist(e);
            }

            // add to message queue
            std::shared_ptr<Data> struct_B(new B(data.get()));
            queue.push(std::move(struct_B));

            // yield:
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
private:
    int N = 5;
    double lo = 0.0;
    double hi = 1.0;
};

#endif