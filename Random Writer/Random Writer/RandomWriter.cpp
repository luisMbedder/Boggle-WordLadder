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
#include <map>
#include <vector>

std::string promptForFile(std::ifstream & infile, std::string prompt);
void processRandomWriter(std::ifstream & infile,int order);

int main() {
	std::ifstream file;
	int markovOrder;
	promptForFile(file, "Enter the source text: ");
	std::cout<< "Enter Markov order [1-10]: ";
	std::cin>>markovOrder;
	processRandomWriter(file,markovOrder);


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

void processRandomWriter(std::ifstream & infile,int order){

	char ch;
	std::map<std::string,std::vector<char> > seedMap;
	std::map<std::string,std::vector<char> >::iterator p;
	//std::vector<char> nextChar;
	std::string str;
	//std::istream_iterator<std::string> iit (std::ifstream infile);
	//iit=infile.begin();

	while(infile.get(ch))//read file one char at a time until eof is reached.
	{
		
		for(int i=0;i<order;i++){
			str +=ch;
			infile.get(ch);
			if(!infile.good())
				break;
		}
		//if(map.count(str))
		p=seedMap.find(str);
		if(p!=seedMap.end()){
			std::vector<char> vecChar = p->second;
		//	seedMap[str]=p->second;//.push_back(infile.peek());
			//seedMap[str]=p->second.push_back(infile.peek()); //"first" correspnds to key, "second" to value, need to use -> to dereference the p iterator
		}
		else{
			char c= infile.peek();
			std::vector<char> nextChar;
			nextChar.push_back(c);
			seedMap.insert(std::pair<std::string,std::vector<char> >(str,nextChar));//nextChar.push_back(infile.peek()));
			//seedMap[str]=std::vector<char> vecChar2 ('d');
		}

		//map.insert(str,nextChar);
		
	//	nextChar.push_back(infile.peek(ch));
		//map.insert(str,nextChar);
		//std::cout<<ch<<std::endl;
	//	std::cout<<infile.peek()<<std::endl;
	//	std::cout<<*iit<<std::endl;
	//	seedMap.insert(ch,ch+infile.g);
	}
	//std::fstream fin("file", fstream::in);
//	while (fin >> noskipws >> ch) {
//		cout << ch; // Or whatever
//	}
	
}