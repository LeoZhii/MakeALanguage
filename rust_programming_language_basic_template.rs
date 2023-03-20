use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn build_codex(codex: &mut Vec<String>, name: &str) {
    //open file from input name
    let script = File::open(name).expect("Failed to open file");

    //collect all lines from file and place in vector codex
    let reader = BufReader::new(script);
    for line in reader.lines() {
        codex.push(line.expect("Failed to read line"));
    }
}

fn read_codex(codex: &Vec<String>) {
    let length = codex.len();
    //read instructions inside codex and interpret results
    for i in 0..length {
        if codex[i] == "print" {
            //if print found increment line by one and print next line
            let next_line = i + 1;
            println!("{}", codex[next_line]);
        }
    }
}

fn main() {
    //vector to hold instruction
    let mut codex: Vec<String> = Vec::new();
    //make sure there is a script listed in the command line argument
    if let Some(name) = env::args().nth(1) {
        //import script
        build_codex(&mut codex, &name);
        //interpret instructions
        read_codex(&codex);
    }
}
