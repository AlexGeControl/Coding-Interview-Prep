#include <cstdlib>
#include <vector>

#include <queue>

#include <algorithm>

#include <iostream>

class Solution {
public:
    /*
    * @param k: An integer
    */
    Solution(int k) : K_(k) {}

    /*
     * @param num: Number to be added
     * @return: nothing
     */
    void add(int num) {
        if ( 0 < K_ ) {
            min_pq_.push(num);
            
            if ( K_ < min_pq_.size() ) min_pq_.pop();
        }
    }

    /*
     * @return: Top k element
     */
    std::vector<int> topk() {
        std::vector<int> result;
        
        if ( 0 < min_pq_.size() ) {
            std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq(min_pq_);
            
            while ( !min_pq.empty() ) {
                result.push_back(min_pq.top());
                min_pq.pop();
            }

            std::reverse(result.begin(), result.end());
        }

        
        return result;
    }
private:
    const size_t K_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq_;
};

int main() {
    Solution solution(3);

    solution.add(3);
    solution.add(10);
    for (const int num: solution.topk()) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    solution.add(1000);
    solution.add(-99);
    for (const int num: solution.topk()) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    solution.add(4);
    for (const int num: solution.topk()) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    solution.add(100);
    for (const int num: solution.topk()) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}