#ifndef BASE_OPERATION_H
#define BASE_OPERATION_H

#include <string>


class BaseOperation {

public:
    virtual std::string operation (std::string) const = 0;
    virtual ~BaseOperation(){};

private:
    std::string m_name; //name of operation
};

#endif