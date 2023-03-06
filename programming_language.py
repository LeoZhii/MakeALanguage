import sys

codex = []

def build_codex():
	global codex
	script = open(sys.argv[1], "r")
	for read_file in script:
		input_to_file = read_file.strip()
		codex.append(input_to_file)
	script.close()
build_codex()

def read_codex():
	global codex
	length = len(codex)
	for line in range(length):
		if (codex[line]=="print"):
			line+=1
			print(codex[line])
read_codex()
