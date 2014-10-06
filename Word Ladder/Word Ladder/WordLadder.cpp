/********************************************************************
* Project : Word Ladder
*
* Created by : LuisMbedder
*
* Description : Implements a word ladder solver using the Breadth-First 
*				search algorithm to find the shortest path solution.
*
* Notes : 
********************************************************************/

#include <iostream>
#include "console.h"
#include <vector>
#include <queue>
#include "lexicon.h"//to get english word list


void solveWordLadder(std::string startWord,std::string endWord);
void printResultVector(std::vector<std::string> resultVector);


/********************************************************************
* Project : Word Ladder
*
* Created by : LuisMbedder
*
* Description : main method
*
* Notes : 
********************************************************************/
int main() {

	std::string startingWord;
	std::string destinationWord;

	while(1)
	{
		std::cout<< "Enter the starting word(or nothing to quit): ";
		if(!std::getline(std::cin,startingWord)){
			return -1; /* i/o error! */
		}
		if(startingWord.empty()){
			std::cout << "Goodbye!" <<std::endl; 
			return 0;
		}
		std::cout<< "Enter the ending word: ";

		if(!std::getline(std::cin,destinationWord)){
			return -1; /* i/o error! */
		}

		if(startingWord.length()==destinationWord.length())
			solveWordLadder(startingWord,destinationWord);
		else{
			std::cout<<"Words must be the same length!"<<std::endl;
		}
		std::cout<<std::endl;
	}

}

/********************************************************************
* function/method : solveWordLadder
*
* startWord : The starting word of the word ladder
* endWord : The target word of the word ladder
*
* Created by : LuisMbedder
*
* Description : Changes the startword progressively by a single letter at a time
*				until the target word is reached. Intermittent words must be
*			    vaild words in the english language. The Breadth-First search 
*				algorithm is used to find the shortes path solution.
*
* Returns: void
*
* Notes : 
********************************************************************/

void solveWordLadder(std::string startWord,std::string endWord){
	
	Lexicon english("EnglishWords.dat");
	std::queue<std::vector<std::string> > ladderQueue;
	std::vector<std::string> currentLadder;
	std::vector<std::string> currentLadderCopy;
	Lexicon wordsAlreadyUsed;
	std::string currentWord;

	currentLadder.push_back(startWord);
	ladderQueue.push(currentLadder);
		
	std::cout<< "Searching..."<<std::endl;

	while(!ladderQueue.empty()){
		std::vector<std::string> lastWord = ladderQueue.front();//access next element
 		//currentLadder.push_back(ladderQueue.front());
		std::string strlastWord = lastWord.back();
		if(lastWord.back() == endWord){
			//return ladderQueue.front();
			std::cout<<"Ladder found: ";
			printResultVector(ladderQueue.front());
			return;
		}
		ladderQueue.pop();
		for(int i =0;i<strlastWord.size();i++)
		{
			std::string tempLastWord = strlastWord;
			for(int j=0;j<26;j++)
			{
				tempLastWord[i]='a'+j;
				if(english.contains(tempLastWord))
				{
					if(wordsAlreadyUsed.contains(tempLastWord)==false){
						currentLadderCopy = lastWord;
						currentLadderCopy.push_back(tempLastWord);
						wordsAlreadyUsed.add(tempLastWord);//update words used list	
						ladderQueue.push(currentLadderCopy);
					}
				}
			}
		}
	}
	std::cout<<"No word latter could be found."<<std::endl;
	return ;
}

/********************************************************************
* function/method : printResultVector
*
* resultVector : holds word ladder solution
*
* Created by : LuisMbedder
*
* Description : Prints the solution
*
* Returns: void
*
* Notes : 
********************************************************************/

void printResultVector(std::vector<std::string> resultVector){
	std::vector<std::string>::iterator vecIt;
	std::string resultStr;

		for(vecIt = resultVector.begin();vecIt!=resultVector.end();vecIt++){
			if(vecIt==resultVector.begin())
				resultStr += *vecIt;
			else
				resultStr+=" -> "+*vecIt;
		}
		std::cout<<resultStr<<std::endl;
		//std::cout<<std::endl;
	}