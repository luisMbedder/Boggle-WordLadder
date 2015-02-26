#ifndef BOGGLE_H
#define BOGGLE_H


#include <iostream>
#include "gboggle.h"
//#include "boggle.h"
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


/********************************************************************
* Constants
********************************************************************/

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int MINIMUM_WORD_LENGTH = 4;
const int BOARD_SIZE =4;

//Dice from the original Boggle game
const std::string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

//used to traverse the adjoining letters of the target letter
const int rdelta[] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int cdelta[] = {-1, 0, 1,-1, 1,-1, 0, 1};



class Boggle
{

public:
    Boggle();
    /********************************************************************
    * Function name : playBoggle
    * Description : sets up and plays the game of boggle.
    ********************************************************************/
    void playBoggle(void);
    /********************************************************************
    * Method name : promptUser
    * Description : promts user for a yes or no answer
    ********************************************************************/
    std::string promptUser(std::string msg,unsigned int msgNumber);

private:

    /********************************************************************
    * Function name : welcome
    * Description : prints out a welcome message
    ********************************************************************/
    void welcome();

    /********************************************************************
    * Function name : giveInstructions
    * Description : print out instructions for the user
    ********************************************************************/
    void giveInstructions();
    /********************************************************************
    * Method name : shuffleCubes
    * board			: reference to the boggle board implemented as a grid of characters
    * cubesVec		: reference to a vector that holds the boggle dice
    * Description : This function "shakes" the boggle dice to generate a
    *				random board configuration.
    ********************************************************************/
    void shuffleCubes(Grid<char> & board,std::vector<std::string> &cubes);
    void setupBoggle(void);
    /********************************************************************
    * Function name : highlightWordPath
    * wordPath		: path to trace on the board
    * Description : this function traces the path on the board by
    *				momentarily highlighting the squares.
    ********************************************************************/
    void highlightWordPath(std::vector<GridPoint>& wordPath);

    /********************************************************************
    * Function name : humansTurn
    * board : The boggle board implemented as a grid of characters
    * Description :
    ********************************************************************/
    void humansTurn(Grid<char> board, std::set<std::string>& usedWords);
    /********************************************************************
    * Function name : computerTurn
    * board			: reference to the boggle board implemented as a grid of characters
    * usedWords     : reference to set of words already used so we dont count them again
    * Description : This function calls bogglesolver for each position on the board.
    ********************************************************************/
    void computerTurn(Grid<char> board,std::set<std::string>& usedWords);
    /********************************************************************
    * Function name : checkLength
    * playerWord	: word player entered.
    * Description : checks if the playerWord meets minimum length requirement
    ********************************************************************/
    bool checkLength(std::string str);
    /********************************************************************
    * Function name : checkWordUsed
    * playerWord	: word player entered.
    * usedWords		: reference to the set of words already used by player.
    * Description : checks if the playerWord is in the usedWord set.
    ********************************************************************/
    bool checkWordUsed(std::string,std::set<std::string>& usedWords);
    /********************************************************************
    * Function name : isEnglishWord
    * playerWord	: word player entered.
    * Description : checks if the playerWord is in the english lexicon.
    ********************************************************************/
    bool isEnglishWord(std::string word);
    /********************************************************************
    * Function name : checkIfValidGuess
    * playerWord	: word to find on board
    * board			: reference to the boggle board implemented as a grid of characters
    * Description : this function calls the recursive boggleSolver function
    *				to check if the playerWord is on the board.
    ********************************************************************/
    bool checkIfValidGuess(std::string playerWord,Grid<char>&board);
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
    bool boggleSolver(Grid<char>& board,int row,int col,std::string playerWord,
                      unsigned int wordIndex,std::vector<GridPoint> &path,std::set<GridPoint> &usedSquares);
    /********************************************************************
    * Function name : computerBoggleSolver
    * board       : reference to the boggle board implemented as a grid of characters
    * row         : boggle board row
    * column      :	boggle board column
    * compWord	  : word to find on board
    * usedSquares : reference to a set that stores the used squares so they
    *			    arent re-used in the same word
    * usedWords	  : reference to the words found by the human player so they arent counted again.
    * Description : This function performs an exhaustive search to find all valid words on the
    *				board.
    ********************************************************************/
    bool computerBoggleSolver(Grid<char>& board,int row,int col,std::string compWord,
                              std::set<GridPoint> &usedSquares,std::set<std::string>& usedWords);

    //lexicon declaration to validate words
 //   Lexicon englishWords("EnglishWords.dat");



};




#endif // BOGGLE_H
