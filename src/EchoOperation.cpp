#include "../include/EchoOperation.h"

std::string
EchoOperation::operation(std::string str) const {
    return str+str;
}