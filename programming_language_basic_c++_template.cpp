#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//build with "g++ programming_language_basic_c++_template.cpp"
//run with commandline "./a.out test.test"

void build_codex(std::vector <std::string> & codex, std::string name) {
	//open file from input name
	std::ifstream script;
	script.open(name);

	//collect all lines from file and place in vector codex
	std::string temp_line;
	while(std::getline(script, temp_line)) {
		codex.push_back(temp_line);
	}
	script.close();
}

void read_codex(std::vector <std::string> & codex) {
	unsigned int length = codex.size();
	//read instructions inside codex and interpret results
	for (unsigned int i = 0; i < length; i++) {
		if (codex[i]=="print") {
			//if print found increment line by one and print next line
			i++;
			std::cout<<codex[i]<<"\n";
		}
	}
}

int main(int argc, char **argv) {
	//vector to hold instruction
	std::vector <std::string> codex;
	//make sure there is a script listed in the command line argument
	if (argc>1) {
		//import script
		build_codex(codex, argv[1]);
		//interpret instructions
		read_codex(codex);
	}
	return 0;
}