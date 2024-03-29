#include "../include/ModuleNetwork.h"
#include <utility>
//#include <iostream>

#define MAX_OUT_TIMES_INPUT 16

ModuleNetwork* ModuleNetwork::instance = 0;
int ModuleNetwork::modCount = 0;

ModuleNetwork*
ModuleNetwork::GetInstance(){
    if(!instance){
        instance = new ModuleNetwork();
    }
    return instance;
}

void
ModuleNetwork::DeleteInstance(){
    if(instance){
        delete instance;
        instance = nullptr;
    }
}

void
ModuleNetwork::UpdateModuleCount(){
    ++modCount;
}

int
ModuleNetwork::GetModuleCount(){
    return modCount;
}

void
ModuleNetwork::addModule(std::shared_ptr<Module> m){
    Mlist adjList;
    //No condition check, as we are adding the modules
    m_modulesMap.insert(std::make_pair(m->getModuleName(),m));
    m_modAdjList.insert(std::make_pair(m,adjList));
}

void
ModuleNetwork::connect(std::string mod1, std::string mod2){
    if(m_modulesMap.find(mod1) == m_modulesMap.end()){
        //std::cout<<"Unable to connect module:"<<mod1<<" , no such module"<<std::endl;
        return;
    }
    if(m_modulesMap.find(mod2) == m_modulesMap.end()){
        //std::cout<<"Unable to connect module:"<<mod2<<" , no such module"<<std::endl;
        return;
    }
    Mptr &m1 = m_modulesMap[mod1];
    Mptr &m2 = m_modulesMap[mod2];
    m2->addIncomingVertex(m1->getModuleName());
    m2->setIncomingInputOrder(ModuleNetwork::GetModuleCount(),m1->getModuleName());
    ModuleNetwork::UpdateModuleCount();

    if(!m_isFirstModSet){
        m_startMod = m1;
        m_startMod->addIncomingVertex(INDEGREE_OF_START); 
        m_isFirstModSet = true;
   }

   //Assuming only added modules will be connected, so additional check for map::find()
   Mlist &adjList = m_modAdjList[m1];
   adjList.push_back(m2);
}

void
ModuleNetwork::process(std::vector<std::string>& vec, std::vector<std::string>& outVec){
    
    if(!m_startMod){
        return;
    }
    
    Mlist queue;
    for(auto &input : vec){
        queue.push_back(m_startMod);
        Mptr vertx = queue.front();
        vertx->addIncomingInput(INDEGREE_OF_START,input);
        while(!queue.empty()){
            vertx = queue.front();
            if (! vertx->performOperation()){
                queue.push_back(vertx);
                queue.pop_front();
            } 

            Mlist &adjList = m_modAdjList[vertx];
            if(adjList.empty()){//if No adjacent node, then this is last node. 
               outVec.push_back(vertx->getOutputValue());
            }
            for(auto &ml : adjList){
                std::string ip = vertx->getOutputValue();
                ml->addIncomingInput(vertx->getModuleName(),ip);
                if(queue.back()->getModuleName() == ml->getModuleName()){
                    continue;
                }
                queue.push_back(ml);
                }
            queue.pop_front();
            }
    }
}