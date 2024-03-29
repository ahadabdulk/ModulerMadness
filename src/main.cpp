#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <regex>

#include "../include/ModuleNetwork.h"
#include "../include/Module.h"

#define COMMAND01 "module"
#define COMMAND02 "connect"
#define COMMAND03 "process"

#define FLUSH ""  //blank string to flush the network in case of delay

#define TIMES_INPUT_STRING 16

using namespace std;

int main(){
    std::string command, operand01, operand02;
    ModuleNetwork *moduleNetwork = ModuleNetwork::GetInstance();
    std::vector<std::string> outVec;
    int in_strings_count = 0; //count of input strings
    int out_strings_count = 0; //count of output strings = max upto 16 time input strings
    if(!moduleNetwork){
        return -1;
    }

    /*std::cout<<"Please Enter your inputs below in following format(Press CTRL+C to exit):\n";
    std::cout<<"module <name> <operation>\n";
    std::cout<<"connect <name1> <name2>\n";
    std::cout<<"process <...list of strings to be processed>"<<endl;
    std::cout<<"---------------------------------------------"<<endl;*/

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
            in_strings_count = veclistOfStrings.size();
            out_strings_count = in_strings_count * TIMES_INPUT_STRING;
            veclistOfStrings.push_back(FLUSH);
            moduleNetwork->process(veclistOfStrings,outVec);
        }

        //Limit the output string to max upto 16 times input string.
        auto endItr = outVec.end();
        if(outVec.size() > out_strings_count){
            endItr = outVec.begin() + out_strings_count;
        }

        std::ostringstream outStream;
        std::string outString;
        std::copy(outVec.begin(),endItr,
			std::ostream_iterator<std::string>(outStream, " "));

        
        //Cleaning up trailing spaces if any
        std::cout<<std::regex_replace(outStream.str(), std::regex(" +$"), "");

        outVec.clear(); 
        
    }

    ModuleNetwork::DeleteInstance();

}