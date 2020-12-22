/*
 * @Description: lock based queue, interface
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_QUEUE_LOCK_BASED_QUEUE_HPP
#define PRODUCER_CONSUMER_QUEUE_LOCK_BASED_QUEUE_HPP

#include <memory>

#include <mutex>
#include <condition_variable>

template <typename T>
class LockBasedQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::unique_ptr<Node> next;

        Node() : data(nullptr), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    Node *tail;

    struct {
        std::mutex head;
        std::mutex tail;
    } mutex;

    std::condition_variable cond;

    /**
     * @brief  get raw tail ptr
     * @param  void
     * @return raw tail ptr                                  
     */
    Node *get_tail(void) {
        std::lock_guard<std::mutex> tail_lock(mutex.tail);
        return tail;
    }

    /**
     * @brief  pop head node
     * @param  void
     * @return raw tail ptr                                  
     */
    std::unique_ptr<Node> pop_head(void) {
        std::unique_ptr<Node> prev_head = std::move(head);
        head = std::move(prev_head->next);
        return prev_head;
    }
    std::unique_lock<std::mutex> wait_and_pop_data(void) {
        std::unique_lock<std::mutex> head_lock(mutex.head);
        cond.wait(head_lock, [&](){ return head.get() != get_tail(); });
        return std::move(head_lock);
    }
    std::unique_ptr<Node> wait_and_pop_head(void) {
        std::unique_lock<std::mutex> head_lock(wait_and_pop_data());
        return pop_head();
    }
    
public:
    LockBasedQueue(): head(new Node), tail(head.get()) {}
    LockBasedQueue(const LockBasedQueue &other) = delete;
    LockBasedQueue & operator=(const LockBasedQueue &other) = delete;

    /**
     * @brief  whether the queue is empty
     * @param  void
     * @return true if the queue is empty false otherwise                                  
     */
    bool empty(void) {
        std::lock_guard<std::mutex> head_lock(mutex.head);
        return head.get() == get_tail();
    }

    /**
     * @brief  push data as shared_ptr into queue
     * @param 
     * @return void                                   
     */
    void push(std::shared_ptr<T> &&data) {
        // allocate node for new data:
        std::unique_ptr<Node> new_node(new Node);
        
        // insert into tail:
        {
            std::lock_guard<std::mutex> tail_lock(mutex.tail);

            tail->data = std::move(data);
            tail->next = std::move(new_node);

            tail = (tail->next).get();
        }

        // notify consumer:
        cond.notify_one();
    }

    /**
     * @brief  pop data as shared_ptr from queue
     * @param 
     * @return void                                   
     */
    std::shared_ptr<T> wait_and_pop(void) {
        std::unique_ptr<Node> prev_head = wait_and_pop_head();

        return prev_head->data;
    }
};

#endif