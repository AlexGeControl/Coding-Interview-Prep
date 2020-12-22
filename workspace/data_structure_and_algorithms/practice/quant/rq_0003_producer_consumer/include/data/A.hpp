/*
 * @Description: Struct A implementation
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_DATA_A_HPP
#define PRODUCER_CONSUMER_DATA_A_HPP

#include "data.hpp"

class A: public Data {
public:
    A(const int a_) : a(a_) { };

    /**
     * @brief  get type
     * @param  void
     * @return data type as enum class Type                                  
     */
    Type GetType(void) const { return Type::A; }

    /**
     * @brief  get data sign
     * @param  void
     * @return data sign as enum class Sign                                   
     */
    Sign GetSign(void) const { return (1 == a % 2) ?  Sign::POSITIVE : Sign::NEGATIVE; }

    /**
     * @brief  get data value
     * @param  void
     * @return data value as double                                   
     */
    double GetValue(void) const { return static_cast<double>(a); }
    
private:
    int a;
};

#endif