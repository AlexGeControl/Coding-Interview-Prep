#include <iostream>
#include <unordered_map>

class TwoSum {
public:
    /**
     * @param number: An integer
     * @return: nothing
     */
    void add(int number) {
        if ( numbers_.end() == numbers_.find(number) ) {
            numbers_[number] = false;
        } else {
            numbers_.at(number) = true;
        }
    }

    /**
     * @param value: An integer
     * @return: Find if there exists any pair of numbers which sum is equal to the value.
     */
    bool find(int value) {
        for (const auto &number_: numbers_) {
            const int source_number = number_.first;
            const bool is_duplicate = number_.second;

            const int target_number = value - source_number;

            const auto &candidate = numbers_.find(target_number);

            if ( numbers_.end() != candidate ) {
                return (target_number == source_number ? is_duplicate : true);
            }
        }

        return false;
    }

private:
    std::unordered_map<int, bool> numbers_;
};

int main() {
    TwoSum two_sum;

    two_sum.add(2);
    two_sum.add(3);

    std::cout << two_sum.find(4) << std::endl;
    std::cout << two_sum.find(5) << std::endl;
    std::cout << two_sum.find(6) << std::endl;
    
    two_sum.add(3);
    std::cout << two_sum.find(6) << std::endl;

    return EXIT_SUCCESS;
}