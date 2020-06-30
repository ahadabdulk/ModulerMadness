#ifndef NOOP_OPERATION_H
#define NOOP_OPERATION_H

#include "BaseOperation.h"

class NoopOperation : public BaseOperation {

public:
    explicit NoopOperation(std::string opName)
    : m_name(opName)
    {}

    std::string operation(std::string) const;

private:
    std::string m_name;


};

#endif