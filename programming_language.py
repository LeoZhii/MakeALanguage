#run with command "python programming_language.py test.test"

import sys

#Store Script
codex = []

def build_codex():
	global codex
	#open script from command line argument
	script = open(sys.argv[1], "r")
	for read_file in script:
		#read every line of file and place in codex
		input_to_file = read_file.strip()
		codex.append(input_to_file)
	script.close()
build_codex()

def read_codex():
	global codex
	length = len(codex)
	for line in range(length):
		#read every line of codex and interpret instructions
		if (codex[line]=="print"):
			#add one to line and print next line after
			line+=1
			print(codex[line])
read_codex()
