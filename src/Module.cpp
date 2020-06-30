#include "../include/Module.h"
#include <iostream>

void
Module::setInputValue(){
    if(m_priorityOrderMap.size() == 0){
        m_input = m_indegreeMap["none"];
        return;
    }
    for(auto i: m_priorityOrderMap){
        m_input += m_indegreeMap[i.second];
    }
}

bool
Module::performOperation(){
    if(m_availableInputs < m_requiredInputs){
        return false;
    }
    else{
        setInputValue();
        m_output = m_op->operation(m_input);
        clearCachedInputs();
        return true;
    }
}

void 
Module::addIncomingVertex(std::string k){
    m_indegreeMap.insert(std::make_pair(k,""));
    ++m_requiredInputs;
}

void 
Module::addIncomingInput(std::string k, std::string v){
    m_indegreeMap[k] = v;
    ++m_availableInputs;
}

void
Module::setIncomingInputOrder(int key, std::string value){
    m_priorityOrderMap.insert(std::make_pair(key,value));

}

void 
Module::clearCachedInputs(){
    m_input = "";
    m_availableInputs = 0;
}
