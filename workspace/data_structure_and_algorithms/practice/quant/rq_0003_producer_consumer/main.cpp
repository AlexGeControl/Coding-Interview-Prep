#include <iostream>

#include <thread>
#include <atomic>

#include "threads/producer_A.hpp"
#include "threads/producer_B.hpp"

#include "data/data.hpp"
#include "queue/lock_based_queue.hpp"

#include "threads/consumer_C.hpp"
#include "threads/consumer_D.hpp"

int main() {
    // producer A: determine data sign
    ProducerA producer_A(1, 100);
    // producer B: determine data value
    ProducerB producer_B(5, 0.0, 1.0);
    // consumer C: maintain real-time sum:
    ConsumerC consumer_C;
    // consumer D: display real-time sum for every 1 second:
    ConsumerD consumer_D;

    // message queue using lock based queue
    LockBasedQueue<Data> queue;
    // real-time sum using atomic int:
    std::atomic<bool> is_available(false);
    std::atomic<int32_t> real_time_sum(0);

    std::thread thread_producer_A(producer_A, std::ref(queue));
    std::thread thread_producer_B(producer_B, std::ref(queue));
    std::thread thread_consumer_C(consumer_C, std::ref(queue), std::ref(is_available), std::ref(real_time_sum));
    std::thread thread_consumer_D(consumer_D, std::ref(is_available), std::ref(real_time_sum));

    thread_producer_A.join();
    thread_producer_B.join();
    thread_consumer_C.join();
    thread_consumer_D.join();

    return EXIT_SUCCESS;
}