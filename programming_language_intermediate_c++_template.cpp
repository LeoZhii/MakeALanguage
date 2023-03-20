#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "hash.h"

//build with "g++ programming_language_basic_c++_template.cpp"
//run with commandline "./a.out test.test"

void build_codex(std::vector <uint64_t> & codex, std::vector <std::string> & string_conts, std::string name) {
	//open file from input name
	std::ifstream script;
	script.open(name);

	//collect all lines from file and place in vector codex
	std::string temp_line;
	uint64_t temp_hash;

	while(std::getline(script, temp_line)) {
		temp_hash = GENHASH(temp_line.c_str());
		switch (temp_hash) {
			case SETHASH("print")://print condition
				codex.push_back(temp_hash);//pass print converted to int into hash
				std::getline(script, temp_line);//read next line
				string_conts.push_back(temp_line);//store string in seperate vector
				codex.push_back(string_conts.size()-1);//pass strings location into codex
				break;
			default:
				codex.push_back(temp_hash);
				break;
		}	
	}
	script.close();
}

void read_codex(std::vector <uint64_t> & codex, std::vector <std::string> & string_conts) {
	unsigned int length = codex.size();
	//read instructions inside codex and interpret results
	for (unsigned int i = 0; i < length; i++) {
		switch(codex[i]) {
			case SETHASH("print"):
				//if print found increment line by one and print next line
				i++;
				std::cout<<string_conts[codex[i]]<<"\n";
				break;
			default:
				std::cout<<"Syntax Error on line: "<<i+1<<"\n";
				break;
		}
	}
}

int main(int argc, char **argv) {
	//vectors to hold instruction
	std::vector <uint64_t> codex;
	std::vector <std::string> string_conts;
	//make sure there is a script listed in the command line argument
	if (argc>1) {
		//import script
		build_codex(codex, string_conts, argv[1]);
		//interpret instructions
		read_codex(codex, string_conts);
	}
	return 0;
}
