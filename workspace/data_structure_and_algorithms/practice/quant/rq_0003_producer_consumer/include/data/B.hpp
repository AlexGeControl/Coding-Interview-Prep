/*
 * @Description: Struct B implementation
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_DATA_B_HPP
#define PRODUCER_CONSUMER_DATA_B_HPP

#include "data.hpp"

class B: public Data {
public:
    static constexpr int kN = 5;

    B(const double *data_) { 
        sum = 0.0;

        for (int i = 0; i < kN; ++i) {
            data[i] = data_[i];
            sum += data_[i];
        }
    };

    /**
     * @brief  get type
     * @param  void
     * @return data type as enum class Type                                  
     */
    Type GetType(void) const { return Type::B; }

    /**
     * @brief  get data sign
     * @param  void
     * @return data sign as enum class Sign                                   
     */
    Sign GetSign(void) const { return Sign::POSITIVE; }

    /**
     * @brief  get data value
     * @param  void
     * @return data value as double                                   
     */
    double GetValue(void) const { return sum; }
    
private:
    double data[kN];
    double sum;
};

#endif