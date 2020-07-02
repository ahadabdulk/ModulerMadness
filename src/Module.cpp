#include "../include/Module.h"
//#include <iostream>

void
Module::setInputValue(){
    if(m_priorityOrderMap.size() == 0){
        // considering the start node's in degree node as none as it is first node in to accept the input.
        m_input = m_indegreeMap[INDEGREE_OF_START];   
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
