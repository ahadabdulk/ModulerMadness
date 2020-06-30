#ifndef DELAY_OPERATION_H
#define DELAY_OPERATION_H

#include "BaseOperation.h"

class DelayOperation : public BaseOperation {

public:
    explicit DelayOperation(std::string opName)
    : m_name(opName)
    , m_buff("hello")
    {}
    
    std::string operation(std::string) const;

    std::string squeezBuffer() const;

private:
    std::string m_name;
    mutable std::string m_buff;   //delay buffer

};

#endif