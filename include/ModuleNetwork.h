#ifndef MODULE_NETWORK_H
#define MODULE_NETWORK_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include "Module.h"

typedef std::shared_ptr<Module> Mptr;
typedef std::list<Mptr> Mlist;
typedef std::map<Mptr,Mlist> ModuleAdjList;
typedef std::map<std::string,Mptr> ModulesMap;

namespace std
{
    template<> struct less<Mptr>
    {
       bool operator() (const Mptr& lhs, const Mptr& rhs) const
       {
           return lhs->getModuleName() < rhs->getModuleName();
       }
    };
}

//Singleton-Class
class ModuleNetwork{

public:
    static ModuleNetwork* GetInstance();
    static void updateModuleCount();
    static int getModuleCount();

    void connect(std::string mod1, std::string mod2);
    void addModule(std::shared_ptr<Module> mod);
    void process(std::vector<std::string>& vec, std::vector<std::string>& outVec);

private:
    ModuleNetwork()
    : m_isFirstModSet(false)
    {}

private:
    static ModuleNetwork* instance;
    static int            modCount;

    ModuleAdjList m_modAdjList;
    ModulesMap m_modulesMap;
    Mptr m_startMod;
    bool m_isFirstModSet;
};

#endif