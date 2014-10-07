/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <string>
#include <fstream>

std::string promptForFile(std::ifstream & infile, std::string prompt);
void processRandomWriter(std::ifstream & infile);

int main() {
	std::ifstream file;
	promptForFile(file, "Enter the source text: ");
	processRandomWriter(file);


    return 0;
}


std::string promptForFile(std::ifstream & infile, std::string prompt){
	while (true){
		std::cout << prompt;
		std::string filename;
		std::getline(std::cin,filename);
		infile.open(filename.c_str());
		if (!infile.fail())
			return filename;
		infile.clear();
		std::cout << "Unable to open file. Try again." << std::endl;
		if (prompt == "")
			prompt = "input file:";

	}

}

void processRandomWriter(std::ifstream & infile){

	char ch;
	while(infile.get(ch))//read file one char at a time until eof is reached.
	{
		std::cout<<ch<<std::endl;
	}
	//std::fstream fin("file", fstream::in);
//	while (fin >> noskipws >> ch) {
//		cout << ch; // Or whatever
//	}
	
}