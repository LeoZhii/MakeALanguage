#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>

std::vector <std::function<void()>> call_stack;

namespace test_lang {

    void language_output(std::string input) {
        std::cout<<input<<"\n";
    }

    void language_interpretor() {
        std::ifstream read_file;
        read_file.open("test.test");
        std::string read_line;
        while (std::getline(read_file, read_line)) {
            if (read_line=="print") {
                std::getline(read_file, read_line);
                call_stack.push_back(std::bind(language_output, read_line));
            }
        }
        read_file.close();
    }

    void language_executor() {
        uint_fast64_t length_of_script = call_stack.size();
        uint_fast64_t line = 0;
        while (line<length_of_script) {
            call_stack[line]();
            line++;
        }
    }
}
int main(int argc, char *argv[]) {
    test_lang::language_interpretor();
    test_lang::language_executor();
    return 42;
}
