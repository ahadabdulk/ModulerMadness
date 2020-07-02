#include "gtest/gtest.h"
#include "ModuleNetwork.h"
#include "Module.h"
#include "EchoOperation.h"
#include "DelayOperation.h"
#include "ReverseOperation.h"
#include "NoopOperation.h"
#include <regex>

using namespace std;
#define FLUSH " " 


class ModuleNetworkTest :  public ::testing::Test{
protected:
    virtual void SetUp() {
        mn = ModuleNetwork::GetInstance();
        std::string command01 = "module";
        std::string command02 = "connect";
        std::string command03 = "process";
    }

    virtual void TearDown() {
        ModuleNetwork::DeleteInstance();
    }

    ModuleNetwork *mn;
};

TEST_F(ModuleNetworkTest, testEcho){
    std::shared_ptr<Module> m1 = std::make_shared<Module>("alpha","echo");
    m1->addIncomingVertex(INDEGREE_OF_START);
    m1->addIncomingInput(INDEGREE_OF_START, "Top");
    m1->performOperation();
    EXPECT_STRCASEEQ("TopTop", m1->getOutputValue().c_str());    
}

TEST_F(ModuleNetworkTest, testReverse){
    std::shared_ptr<Module> m1 = std::make_shared<Module>("beta","reverse");
    m1->addIncomingVertex(INDEGREE_OF_START);
    m1->addIncomingInput(INDEGREE_OF_START, "Top");
    m1->performOperation();
    EXPECT_STRCASEEQ("poT", m1->getOutputValue().c_str());    
}

TEST_F(ModuleNetworkTest, testDelay){
    std::shared_ptr<Module> m1 = std::make_shared<Module>("alpha","delay");
    m1->addIncomingVertex(INDEGREE_OF_START);
    m1->addIncomingInput(INDEGREE_OF_START, "Top");
    m1->performOperation();
    EXPECT_STRCASEEQ("hello", m1->getOutputValue().c_str());    
}

TEST_F(ModuleNetworkTest, testNoop){
    std::shared_ptr<Module> m1 = std::make_shared<Module>("alpha","noop");
    m1->addIncomingVertex(INDEGREE_OF_START);
    m1->addIncomingInput(INDEGREE_OF_START, "Top");
    m1->performOperation();
    EXPECT_STRCASEEQ("Top", m1->getOutputValue().c_str());    
}

TEST_F(ModuleNetworkTest, testAllThreeCommands){
    mn = ModuleNetwork::GetInstance();

    //Taking input of two modules (alpha and beta) with operation (reverse and delay)
    std::shared_ptr<Module> mod01 = std::make_shared<Module>("alpha","reverse");
    std::shared_ptr<Module> mod02 = std::make_shared<Module>("beta","delay");

    mn->addModule(mod01);
    mn->addModule(mod02);

    //connect alpha ---> beta
    mn->connect(mod01->getModuleName(),mod02->getModuleName());

    //process hello world
    std::vector<std::string> in = {"hello", "world", FLUSH};
    std::vector<std::string> out;

    mn->process(in, out);
    std::ostringstream oss;
    std::string os;
    std::copy(out.begin(), out.end(), std::ostream_iterator<std::string>(oss, " "));
    os = oss.str();
    os = std::regex_replace(os, std::regex(" +$"), "");

    EXPECT_STRCASEEQ("hello olleh dlrow", os.c_str()); 
}

TEST_F(ModuleNetworkTest, testSerialNodes){
    mn = ModuleNetwork::GetInstance();
    
    //Taking input of two modules (alpha and beta) with operation (reverse and delay)
    std::shared_ptr<Module> mod01 = std::make_shared<Module>("alpha","reverse");
    std::shared_ptr<Module> mod02 = std::make_shared<Module>("beta","noop");
    std::shared_ptr<Module> mod03 = std::make_shared<Module>("gaama","reverse");
    std::shared_ptr<Module> mod04 = std::make_shared<Module>("delta","echo");
    std::shared_ptr<Module> mod05 = std::make_shared<Module>("theta","delay");

    mn->addModule(mod01);
    mn->addModule(mod02);
    mn->addModule(mod03);
    mn->addModule(mod04);
    mn->addModule(mod05);

    mn->connect(mod01->getModuleName(),mod02->getModuleName());  //aplha-->beta
    mn->connect(mod02->getModuleName(),mod03->getModuleName());  //alpha-->gaama
    mn->connect(mod03->getModuleName(),mod04->getModuleName());
    mn->connect(mod04->getModuleName(),mod05->getModuleName());

    //process hello world
    std::vector<std::string> in = {"Top", "Gun", FLUSH};
    std::vector<std::string> out;

    mn->process(in, out);
    std::ostringstream oss;
    std::string os;
    std::copy(out.begin(), out.end(), std::ostream_iterator<std::string>(oss, " "));
    os = oss.str();
    os = std::regex_replace(os, std::regex(" +$"), "");

    EXPECT_STRCASEEQ("hello TopTop GunGun", os.c_str()); 
}


//Test Summing, Summing up multiple inputs to a module, also in order in which they appear
TEST_F(ModuleNetworkTest, testSumming){
    mn = ModuleNetwork::GetInstance();
    
    //Taking input of two modules (alpha and beta) with operation (reverse and delay)
    std::shared_ptr<Module> mod01 = std::make_shared<Module>("alpha","reverse");
    std::shared_ptr<Module> mod02 = std::make_shared<Module>("beta","noop");
    std::shared_ptr<Module> mod03 = std::make_shared<Module>("gaama","reverse");
    std::shared_ptr<Module> mod04 = std::make_shared<Module>("delta","echo");
    //std::shared_ptr<Module> mod05 = std::make_shared<Module>("theta","delay");

    mn->addModule(mod01);
    mn->addModule(mod02);
    mn->addModule(mod03);
    mn->addModule(mod04);
    //mn->addModule(mod05);

    mn->connect(mod01->getModuleName(),mod02->getModuleName());  //aplha-->beta
    mn->connect(mod01->getModuleName(),mod03->getModuleName());  //alpha-->gaama
    mn->connect(mod02->getModuleName(),mod04->getModuleName());
    mn->connect(mod03->getModuleName(),mod04->getModuleName());
    //mn->connect(mod04->getModuleName(),mod05->getModuleName());

    //process hello world
    std::vector<std::string> in = {"Top",FLUSH};
    std::vector<std::string> out;

    mn->process(in, out);
    std::ostringstream oss;
    std::string os;
    std::copy(out.begin(), out.end(), std::ostream_iterator<std::string>(oss, " "));
    os = oss.str();
    os = std::regex_replace(os, std::regex(" +$"), "");

    EXPECT_STRCASEEQ("poTToppoTTop", os.c_str()); 
}


TEST_F(ModuleNetworkTest, testSumming2){
    mn = ModuleNetwork::GetInstance();
    
    //Taking input of two modules (alpha and beta) with operation (reverse and delay)
    std::shared_ptr<Module> mod01 = std::make_shared<Module>("alpha","reverse");
    std::shared_ptr<Module> mod02 = std::make_shared<Module>("beta","noop");
    std::shared_ptr<Module> mod03 = std::make_shared<Module>("gaama","reverse");
    std::shared_ptr<Module> mod04 = std::make_shared<Module>("delta","echo");
    //std::shared_ptr<Module> mod05 = std::make_shared<Module>("theta","delay");

    mn->addModule(mod01);
    mn->addModule(mod02);
    mn->addModule(mod03);
    mn->addModule(mod04);
    //mn->addModule(mod05);

    mn->connect(mod01->getModuleName(),mod02->getModuleName());  //aplha-->beta
    mn->connect(mod01->getModuleName(),mod03->getModuleName());  //alpha-->gaama
    mn->connect(mod02->getModuleName(),mod04->getModuleName());
    mn->connect(mod03->getModuleName(),mod04->getModuleName());
    //mn->connect(mod04->getModuleName(),mod05->getModuleName());

    //process hello world
    std::vector<std::string> in = {"Hb","Ti",FLUSH};
    std::vector<std::string> out;

    mn->process(in, out);
    std::ostringstream oss;
    std::string os;
    std::copy(out.begin(), out.end(), std::ostream_iterator<std::string>(oss, " "));
    os = oss.str();
    os = std::regex_replace(os, std::regex(" +$"), "");
    EXPECT_STRCASEEQ("bHHbbHHb iTTiiTTi", os.c_str()); 
}
