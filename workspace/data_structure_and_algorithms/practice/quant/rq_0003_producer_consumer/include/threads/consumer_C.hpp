/*
 * @Description: consumer C implementation
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_THREAD_CONSUMER_C_HPP
#define PRODUCER_CONSUMER_THREAD_CONSUMER_C_HPP

#include <iostream>
#include <iomanip>

#include "data/data.hpp"
#include "queue/lock_based_queue.hpp"

#include <atomic>

class ConsumerC {
public:
    ConsumerC() {}

    void operator()(LockBasedQueue<Data> &queue, std::atomic<bool> &is_available, std::atomic<int32_t> &real_time_sum) {
        bool is_positive = true;
        double sum = 0.0;

        // mark real-time sum as initialized:
        is_available.store(true, std::memory_order_release);

        while (true) {
            // retrieve message:
            std::shared_ptr<Data> msg = queue.wait_and_pop();

            // process message:
            switch( msg->GetType() ) {
                case Data::Type::A:
                    is_positive = (Data::Sign::POSITIVE == msg->GetSign());
                    break;
                case Data::Type::B:
                    if ( is_positive ) {
                        sum += msg->GetValue();
                    } else {
                        sum -= msg->GetValue();
                    }
                    break;
                default:
                    break;
            }

            // save to real-time sum:
            real_time_sum.store(
                static_cast<int32_t>(100 * sum),
                std::memory_order_release
            );
        }
    }
};

#endif