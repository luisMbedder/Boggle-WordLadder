/********************************************************************
* Project : Boggle
*
* Created by : LuisMbedder
*
* Description : Implements the game of Boggle adapted for a human player
* against the computer. The heart of the program consists of two recursive
* backtracking algorithms to find words on the board, one for the human player
* and another for the computer. The computer proves nearly impossible
* to beat since it has a lexicon at its disposal! 
*
* Notes : None.
********************************************************************/

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "GridPoint.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
#include <boost/algorithm/string.hpp>

/********************************************************************
* Constants
********************************************************************/

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int MINIMUM_WORD_LENGTH = 4;
const int BOARD_SIZE =4;

//Dice from the original Boggle game
const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

//used to traverse the adjoining letters of the target letter 
const int rdelta[] = {-1,-1,-1, 0, 0, 1, 1, 1}; 
const int cdelta[] = {-1, 0, 1,-1, 1,-1, 0, 1};

/********************************************************************
* function prototypes
********************************************************************/

void welcome();
void giveInstructions();
void shuffleCubes(Grid<char> & board,std::vector<std::string> &cubes);
void setupBoggle(void);
void highlightWordPath(std::vector<GridPoint>& wordPath);
void playBoggle(void);
void humansTurn(Grid<char> board, std::set<std::string>& usedWords);
void computerTurn(Grid<char> board,std::set<std::string>& usedWords);
bool checkLength(std::string str);
bool checkWordUsed(std::string,std::set<std::string>& usedWords);
bool isEnglishWord(std::string word);
bool checkIfValidGuess(string playerWord,Grid<char>&board);
bool boggleSolver(Grid<char>& board,int row,int col,std::string playerWord,
				  unsigned int wordIndex,std::vector<GridPoint> &path,std::set<GridPoint> &usedSquares);
bool computerBoggleSolver(Grid<char>& board,int row,int col,std::string compWord,
						  std::set<GridPoint> &usedSquares,std::set<std::string>& usedWords);

//lexicon declaration to validate words
Lexicon englishWords("EnglishWords.dat");

/********************************************************************
* Main program
********************************************************************/

int main() {
	
	//setupBoggle();
	playBoggle();

    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}


/********************************************************************
* Function name : playBoggle
*
* Created by	: LuisMbedder
*
* Description : sets up and plays the game of boggle. 
*
* Notes : None
********************************************************************/
void playBoggle(){
	
	Grid<char> board(BOARD_SIZE, BOARD_SIZE);
    std::vector<std::string> cubesVec;
	std::set<std::string> usedWords;
	srand((unsigned int)std::time(NULL));
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
	drawBoard(4,4);
    shuffleCubes(board,cubesVec);
    welcome();
    giveInstructions();

	
	humansTurn(board,usedWords);
	computerTurn(board,usedWords);
	

}

/********************************************************************
* Function name : humansTurn
*
* board			: The boggle board implemented as a grid of characters
*
* Created by : LuisMbedder
*
* Description : 
*
* Notes : None
********************************************************************/
void humansTurn(Grid<char> board,std::set<std::string>& usedWords){
	std::string userWord;
	std::vector<std::string> humanWordList;

	while(1){
	std::cout << "Enter a Word: ";
		if(!std::getline(std::cin,userWord)){
		break; /* i/o error! */
		}
	if(userWord.empty()){
	  //	std::cout << "Would you like to play again?";
	//	if(!std::getline(std::cin,userWord))
	//		break;// i/o error
	//	if(userWord=="n")
		//	break;
		break;
	}
	boost::to_upper(userWord);

	if(checkLength(userWord)&&checkWordUsed(userWord,usedWords)&&isEnglishWord(userWord)){
		if(checkIfValidGuess(userWord,board)){
			humanWordList.push_back(userWord);//dont really need this
			usedWords.insert(userWord);
		}
		else{
			std::cout<<"Cannot make that word on board"<<std::endl;
		}
	}

	}
}

/********************************************************************
* Function name : shuffleCubes
*
* board			: reference to the boggle board implemented as a grid of characters
* cubesVec		: reference to a vector that holds the boggle dice
*
* Created by : LuisMbedder
*
* Description : This function "shakes" the boggle dice to generate a
*				random board configuration. 
********************************************************************/
void shuffleCubes(Grid<char> &board,std::vector<std::string> &cubesVec){

    unsigned arraySize =sizeof(STANDARD_CUBES)/sizeof(STANDARD_CUBES[0]);
    copy(&STANDARD_CUBES[0],&STANDARD_CUBES[arraySize],back_inserter(cubesVec));
	int k=0;

    for(unsigned int i=0;i<cubesVec.size();i++){
        int r=rand()%(arraySize-i)+i;//generate a random int between arraySize and i, inclusive
		std::iter_swap(cubesVec.begin()+i,cubesVec.begin()+r);
    }
	for(int i=0;i<BOARD_SIZE;i++){
		for(int j=0;j<BOARD_SIZE;j++){
			std::string lettersOnCube = cubesVec[k];
			char letter = lettersOnCube[rand()%6];//choose a random side of dice to put "face up"
			board[i][j]=letter;
			labelCube(i,j,letter);
			k++;
		}
	}
}

/********************************************************************
* Function name : checkLength
*
* playerWord	: word player entered. 
*
* Created by : LuisMbedder
*
* Description : checks if the playerWord meets minimum length requirement
********************************************************************/
bool checkLength(std::string playerWord){
	if(playerWord.length()<MINIMUM_WORD_LENGTH){
		std::cout <<"That word doesn't meet the minimum word length."<<std::endl;
		return false;
	}
		return true;	
}

/********************************************************************
* Function name : checkWordUsed
*
* playerWord	: word player entered. 
* usedWords		: reference to the set of words already used by player. 
*
* Created by : LuisMbedder
*
* Description : checks if the playerWord is in the usedWord set. 
********************************************************************/
bool checkWordUsed(std::string playerWord,std::set<std::string>& usedWords){

	if(std::find(usedWords.begin(),usedWords.end(),playerWord)!=usedWords.end()){
		std::cout<<	"You've already found that word!"<<std::endl;
		return false;
	}
		return true;
}

/********************************************************************
* Function name : isEnglishWord
*
* playerWord	: word player entered. 
*
* Created by : LuisMbedder
*
* Description : checks if the playerWord is in the english lexicon. 
********************************************************************/
bool isEnglishWord(std::string playerWord){		

//	if(!englishWords.contains(word)){
//		std::cout <<"That's not a word!"<<std::endl;
//		return false;
//	}
	return true;

}


/********************************************************************
* Function name : highlightWordPath
*
* wordPath		: path to trace on the board
*
* Created by: LuisMbedder
*
* Description : this function traces the path on the board by 
*				momentarily highlighting the squares.
********************************************************************/
void highlightWordPath(std::vector<GridPoint>& wordPath){
	std::vector<GridPoint>::iterator it;
	for(it=wordPath.begin();it<wordPath.end();it++){
		GridPoint p1 = *it;
		int x = p1.getX();
		int y = p1.getY();
		highlightCube(x,y,true);

	}

	pause(200);

	for(it=wordPath.begin();it<wordPath.end();it++){
		GridPoint p1 = *it;
		int x = p1.getX();
		int y = p1.getY();
		highlightCube(x,y,false);
	}
}


/********************************************************************
* Function name : checkIfValidGuess
*
* playerWord	: word to find on board
* board			: reference to the boggle board implemented as a grid of characters
*
* Created by : LuisMbedder
*
* Description : this function calls the recursive boggleSolver function
*				to check if the playerWord is on the board.
********************************************************************/
bool checkIfValidGuess(string playerWord,Grid<char>&board){

	//char startLetter = playerWord[0];//delete
    std::vector<GridPoint> path;
	std::set<GridPoint> usedSquares;
	int index =0;

	for(int row=0;row<BOARD_SIZE;row++){
		for(int col=0;col<BOARD_SIZE;col++){
			if(boggleSolver(board,row,col,playerWord,index,path,usedSquares)){
				highlightWordPath(path);
				recordWordForPlayer(playerWord, HUMAN);
				return true;//word was found in board.
			}
	    }
	}	
	return false;//word is not in the board
}


/**********************************************************************
* Function name : boggleSolver
*
* board       : reference to the boggle board implemented as a grid of characters
* row         : boggle board row
* column      :	boggle board column
* playerWord  : word to find on board
* wordIndex   : the letter in playerWord that is being searched for
* path        : reference to a vector that holds the path of matched letters
* usedSquares : reference to a set that stores the usedsquares so they 
*			    arent re-used in the same word  
*
* Created by  : LuisMbedder
*
* Description : This function searches for the player word on the 
*				board usign a recursive backtracking algorithm. It will return a boolean indicating wether
*				or not the word was found on the board. 
*		
*				Base case: If the index of the word is greater than the length
*						   of the word then we have found all letters and it succeeded. 
*				
*				Otherwise, it finds a valid letter on the board, records its postion and
*				recursively calls boggleSovler upto 8 times to search for the next letter 
*				in the adjoining spaces of that letter. If after 8 calls no letter is 
*				found, then we undo the latest valid letter entry and search for another 
*				valid letter in the remianing spaces by returning false to the calling
*				function(checkifValidGuess). The process repeats  until a word has been 
*				found or we have exhausted all rows and columns on the board. 			
***********************************************************************************/
bool boggleSolver(Grid<char>& board,int row,int col,std::string playerWord,unsigned int wordIndex,std::vector<GridPoint> &path,std::set<GridPoint> &usedSquares){
	
	if(wordIndex>playerWord.length()-1){//base case, return true if word is found
		return true;
	}
	if(!board.inBounds(row,col)){//if board location is out-of-bounds go on to the next square
		return false;
	}

		std::set<GridPoint>::iterator it;
		char c = board.get(row,col);
		if(playerWord[wordIndex]==board.get(row,col)){
			GridPoint pt;
			pt.x=row;
			pt.y=col;
			it=usedSquares.find(pt);
			if(usedSquares.find(pt)!=usedSquares.end())					
				return false;
			path.push_back(pt);
			usedSquares.insert(pt);
			wordIndex++;
			for(int i=0;i<sizeof(rdelta)/sizeof(rdelta[0]);i++){//recurively search the 8 spaces around the target letter
				if(boggleSolver(board,row+rdelta[i],col+cdelta[i],playerWord,wordIndex,path,usedSquares))
					return true;
			}
			    path.pop_back();//gets here when it cant find another letter in the adjoining spaces, undo the latest entry and try again. 
				usedSquares.erase(pt);
		}
		return false;//this triggers backtracking from early decisions
}


/********************************************************************
* Function name : computerTurn
*
* board			: reference to the boggle board implemented as a grid of characters
* usedWords     : reference to set of words already used so we dont count them again
*
* Created by : LuisMbedder
*
* Description : This function calls bogglesolver for each position on the board. 
********************************************************************/
void computerTurn(Grid<char> board,std::set<std::string>& usedWords){

	std::set<GridPoint> usedSquares;
	std::string word ="";
	int index =0;

	for(int row=0;row<BOARD_SIZE;row++){
		for(int col=0;col<BOARD_SIZE;col++){
			if(computerBoggleSolver(board,row,col,word,usedSquares,usedWords)){
				std::string wordFound = word;
				//recordWordForPlayer(word, COMPUTER);
				//return true;//word was found in board.
			}
		}
	}	
}

/********************************************************************
* Function name : computerBoggleSolver
*
* board       : reference to the boggle board implemented as a grid of characters
* row         : boggle board row
* column      :	boggle board column
* compWord	  : word to find on board
* usedSquares : reference to a set that stores the usedsquares so they 
*			    arent re-used in the same word 
* usedWords	  : reference to the words found by the human player so they arent counted again. 
*
* Created by : LuisMbedder
*
* Description : 
********************************************************************/
bool computerBoggleSolver(Grid<char>& board,int row,int col,std::string compWord,std::set<GridPoint> &usedSquares,std::set<std::string>& usedWords){

		if(!board.inBounds(row,col)){//if board location is out-of-bounds go on to the next square
			return false;
		}
		GridPoint pt(row,col);
		if(usedSquares.find(pt)!=usedSquares.end())					
				return false;
		//if(word.size()<3)
		//	return false;
		char c = board[row][col];
		

		if(englishWords.containsPrefix(compWord)||compWord.size()<3){
			usedSquares.insert(pt);
			compWord+=board[row][col];
			if(englishWords.contains(compWord)&&compWord.size()>3
				&&std::find(usedWords.begin(),usedWords.end(),compWord)==usedWords.end()){
					usedWords.insert(compWord);
					recordWordForPlayer(compWord, COMPUTER);
			}
		
		for(int i=0;i<sizeof(rdelta)/sizeof(rdelta[0]);i++){
			if((!englishWords.containsPrefix(compWord))&&compWord.size()>2)
				break;//dont bother searching for next letter if current word is not a valid prefix
			if(computerBoggleSolver(board,row+rdelta[i],col+cdelta[i],compWord,usedSquares,usedWords))
			{
					return true;
			}
		}
		usedSquares.erase(pt);
		compWord.erase(compWord.size()-1,1);
		}
		
		return false;

}


