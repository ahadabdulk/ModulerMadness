#ifndef MODULE_H_
#define MODULE_H_
#include <string>
#include <map>

#include "BaseOperation.h"
#include "EchoOperation.h"
#include "ReverseOperation.h"
#include "NoopOperation.h"
#include "DelayOperation.h"

#define INDEGREE_OF_START "none"

typedef std::map<std::string,std::string> IndegreeMap;
typedef std::map<int,std::string> PriorityOrder;

class Module{
public:
    Module(std::string modName, std::string opName)
    : m_moduleName(modName)
    , m_opName(opName)
    , m_input("")
    , m_output("")
    , m_requiredInputs(0)
    , m_availableInputs(0)
    {
        if("echo" == opName){
            m_op = new EchoOperation(opName);
        }
        else if("reverse" == opName){
            m_op = new ReverseOperation(opName);
        }
        else if("noop" == opName){
            m_op = new NoopOperation(opName);
        }
        else if("delay" == opName){
            m_op =new DelayOperation(opName);
        }
        else{
            m_op = nullptr;
        }
    }
    const std::string& getModuleName() const { return m_moduleName; }
    const std::string& getOpName() const { return m_opName; }

    bool performOperation();

    //void setInputValue(std::string& input);
    void setInputValue();
    
    std::string getInputValue() const { return m_input; }
    std::string getOutputValue() const { return m_output; }

    void addIncomingVertex(std::string key);
    void addIncomingInput(std::string k, std::string v);

    void setIncomingInputOrder(int key, std::string value);
    void clearCachedInputs();

private:
    std::string m_moduleName;
    std::string m_opName;
    std::string m_input;
    std::string m_output;
    BaseOperation* m_op;
    IndegreeMap m_indegreeMap;
    int         m_requiredInputs;
    int         m_availableInputs;
    PriorityOrder  m_priorityOrderMap;
};

#endif