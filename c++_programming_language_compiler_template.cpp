#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>

//build with "g++ programming_language_basic_c++_template.cpp"
//run with commandline "./a.out test.test"

void build_codex(std::string name) {
	//open file from input name
	std::ifstream script;
	script.open(name);
	
	std::ofstream compile_driver;//create new file based on input name
	compile_driver.open(name+".cpp", std::ofstream::trunc);
	
	//place prerequisite c++ code in file
	compile_driver<<"#include <iostream>"<<std::endl<<"int main() {";
	//read script
	std::string temp_line;
	while(std::getline(script, temp_line)) {
		//if script contains print add std::cout statement to file with next line
		if (temp_line=="print") {
			std::getline(script, temp_line);
			compile_driver<<"std::cout<<\""<<temp_line<<"\\n\";"<<std::endl;
		}
	}
	//close off files
	compile_driver<<" return 0;}\n";
	script.close();
	compile_driver.close();
	//compile c++ code with g++ into binary using system call
	std::string compile_command = "g++ -o \""+name+".out\" -std=c++11 "+name+".cpp";
	system(compile_command.c_str());
}

int main(int argc, char **argv) {
	//make sure there is a script listed in the command line argument
	if (argc>1) {
		//import script and compile
		build_codex(argv[1]);
	}
	return 0;
}
