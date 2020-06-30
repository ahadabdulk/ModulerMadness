#ifndef ECHO_OPERATION_H
#define ECHO_OPERATION_H

#include "BaseOperation.h"

class EchoOperation : public BaseOperation {

public: 
    explicit EchoOperation(std::string opName)
    : m_name(opName)
    {}

    std::string operation(std::string) const;

private:
    std::string m_name;
};

#endif