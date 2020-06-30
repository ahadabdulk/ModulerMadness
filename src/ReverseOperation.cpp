#include "../include/ReverseOperation.h"
#include <algorithm>

std::string
ReverseOperation::operation (std::string str) const {

     std::reverse(str.begin(), str.end());
     return str;

}