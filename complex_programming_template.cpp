#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>

namespace test_lang {
    //function to output text to console
    void language_output(std::string input) {
        std::cout<<input<<"\n";
    }
    
    //read textfile and translate instructions into pointer addresses
    void language_interpretor(std::vector <std::function<void()>> & call_stack, std::string name) {
        std::ifstream read_file;
        read_file.open(name);
        std::string read_line;
        //read entire file
        while (std::getline(read_file, read_line)) {
            //if print read next line and bind to call_stack
            if (read_line=="print") {
                std::getline(read_file, read_line);
                call_stack.push_back(std::bind(language_output, read_line));
            }
        }
        read_file.close();
    }

    void language_executor(std::vector <std::function<void()>> & call_stack) {
        uint_fast64_t length_of_script = call_stack.size();
        uint_fast64_t line = 0;
        //based on length of call_stack call instructions
        while (line<length_of_script) {
            call_stack[line]();
            line++;
        }
    }
}
int main(int argc, char *argv[]) {
    //vector to store pointer instructions
    std::vector <std::function<void()>> call_stack;
    //call hybrid components
    if (argc>1) {
        test_lang::language_interpretor(call_stack, argv[1]);
        test_lang::language_executor(call_stack);
    }
    return 42;
}
