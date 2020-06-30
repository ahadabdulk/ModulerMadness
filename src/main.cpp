#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../include/ModuleNetwork.h"
#include "../include/Module.h"

#define COMMAND01 "module"
#define COMMAND02 "connect"
#define COMMAND03 "process"

using namespace std;

int main(){
    std::string command, operand01, operand02;
    ModuleNetwork *moduleNetwork = ModuleNetwork::GetInstance();
    /*******/
    //std::vector<std::string> vvv;
    //vvv.push_back("Hello");
    //vvv.push_back("World");
    /******/
    
    if(!moduleNetwork){
        return -1;
    }

    std::cout<<"Please Enter your inputs below in following format(Press CTRL+C to exit):\n";
    std::cout<<"module <name> <operation>\n";
    std::cout<<"connect <name1> <name2>\n";
    std::cout<<"process <...list of strings to be processed>\n"<<endl;

    while(1){
        std::cin >> command;
        // Input type 01 - module
        if( COMMAND01 == command ){                     
            std::cin >> operand01 >> operand02;         //Taking module name and operation value
            std::shared_ptr<Module> mptr = std::make_shared<Module>(operand01, operand02);
            moduleNetwork->addModule(mptr);
        }
        //Input type 02 - connect
        else if( COMMAND02 == command ){ 
            std::cin >> operand01 >> operand02; // Taking module names as input
            moduleNetwork->connect(operand01,operand02);
        }
        //Input type 03 - process
        else if( COMMAND03 == command ){  
            std::getline (std::cin,operand01);
            std::stringstream ss(operand01);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> veclistOfStrings(begin, end);
            //std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

            //std::cout<<"\n"<<moduleNetwork->process(veclistOfStrings)<<endl;
            moduleNetwork->process(veclistOfStrings);
        }
        
    }

}