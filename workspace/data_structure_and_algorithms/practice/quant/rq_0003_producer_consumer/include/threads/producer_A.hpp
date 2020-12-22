/*
 * @Description: producer A implementation
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_THREAD_PRODUCER_A_HPP
#define PRODUCER_CONSUMER_THREAD_PRODUCER_A_HPP

#include <iostream>

#include <random>

#include <thread>
#include <chrono>

#include <memory>

#include "data/A.hpp"

#include "data/data.hpp"
#include "queue/lock_based_queue.hpp"

class ProducerA {
public:
    ProducerA(const int lo_, const int hi_) : lo(lo_), hi(hi_) {}

    void operator()(LockBasedQueue<Data> &queue) {
        // init random integer generator:
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution<int> uniform_dist(lo, hi);
        
        while (true) {
            // generate a random integer between 1 and 100:
            int a = uniform_dist(e);

            // add to message queue:
            std::shared_ptr<Data> struct_A(new A(a));
            queue.push(std::move(struct_A));

            // yield:
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
private:
    int lo = 1;
    int hi = 100;
};

#endif