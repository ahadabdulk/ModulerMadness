#include "../include/DelayOperation.h"

std::string
DelayOperation::operation(std::string str) const {

    std::string temp = m_buff;
    m_buff = str;

    return temp;  
}


std::string
DelayOperation::squeezBuffer() const {
    return m_buff;
}