#ifndef REVERSE_OPERATION_H
#define REVERSE_OPERATION_H

#include "BaseOperation.h"

class ReverseOperation : public BaseOperation {

public:
    explicit ReverseOperation(std::string opName)
    : m_name(opName)
    {}

    std::string operation(std::string) const;

private:
    std::string m_name;


};

#endif