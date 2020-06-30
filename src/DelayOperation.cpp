#include "../include/DelayOperation.h"

std::string
DelayOperation::operation(std::string str) const {

    if(m_buff == " "){
        m_buff = "hello";
    }
    std::string temp = m_buff;
    m_buff = str;

    return temp;  
}