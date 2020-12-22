/*
 * @Description: General data interface
 * @Author: Ge Yao
 * @Date: 2020-12-21 20:35:07
 */
#ifndef PRODUCER_CONSUMER_DATA_DATA_HPP
#define PRODUCER_CONSUMER_DATA_DATA_HPP

class Data {
public:
    // type:
    enum class Type:char {
        A,
        B
    };

    // sign:
    enum class Sign:char {
        POSITIVE,
        NEGATIVE
    };

    /**
     * @brief  get type
     * @param  void
     * @return data type as enum class Type                                  
     */
    virtual Type GetType(void) const = 0;

    /**
     * @brief  get data sign
     * @param  void
     * @return data sign as enum class Sign                                   
     */
    virtual Sign GetSign(void) const = 0;

    /**
     * @brief  get data value
     * @param  void
     * @return data value as double                                   
     */
    virtual double GetValue(void) const = 0;
};

#endif