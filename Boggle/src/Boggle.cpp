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
* Notes : See Boggle.h for documentation
********************************************************************/

#include <iostream>
#include "gboggle.h"
#include "boggle.h"
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




//lexicon declaration to validate words
Lexicon englishWords("EnglishWords.dat");

Boggle::Boggle(){
    welcome();
    promptUser("Do you need instructions? ",0);

}

std::string Boggle::promptUser(std::string msg,unsigned int msgNumber){
    std::cout<<msg;
    std::string result="";
    while(true){
    std::getline(std::cin,result);
    std::transform(result.begin(), result.end(), result.begin(),toupper);
    if(result=="Y"&&msgNumber==0){
        giveInstructions();
        break;
    }
    else if(result=="Y"&&msgNumber==1){
        break;//return result;
    }
    else if(result=="N")
        break;
    else
        std::cout<<"Please enter y or n. ";
    }
    return result;
}


void Boggle::welcome() {
    std::cout << "Welcome!  You're about to play a classic game ";
    std::cout << "of Boggle." <<  std::endl <<  std::endl;
}



void Boggle::giveInstructions() {
    std::cout << std::endl;
    std::cout << "The boggle board is a grid onto which I ";
    std::cout << "I will randomly distribute cubes. These ";
    std::cout << "6-sided cubes have letters rather than ";
    std::cout << "numbers on the faces, creating a grid of ";
    std::cout << "letters on which you try to form words. ";
    std::cout << "You go first, entering all the words you can ";
    std::cout << "find that are formed by tracing adjoining ";
    std::cout << "letters. Two letters adjoin if they are next ";
    std::cout << "to each other horizontally, vertically, or ";
    std::cout << "diagonally. A letter can only be used once ";
    std::cout << "in each word. Words must be at least four ";
    std::cout << "letters long and can be counted only once. ";
    std::cout << "You score points based on word length: a ";
    std::cout << "4-letter word is worth 1 point, 5-letters ";
    std::cout << "earn 2 points, and so on." <<  std::endl <<  std::endl;
    std::cout << "Hit return when you're ready...";
    getLine();
}


void Boggle::playBoggle(){

    Grid<char> board(BOARD_SIZE, BOARD_SIZE);
    std::vector<std::string> cubesVec;
    std::set<std::string> usedWords;
    srand((unsigned int)std::time(NULL));
    static GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   // gw.drawImage("background.jpg", pt);
      //  GImage gimage = new GImage(image);

    initGBoggle(gw);
    drawBoard(4,4);
    shuffleCubes(board,cubesVec);

    humansTurn(board,usedWords);
    computerTurn(board,usedWords);

}


void Boggle::humansTurn(Grid<char> board,std::set<std::string>& usedWords){
    std::string userWord;
    std::vector<std::string> humanWordList;

    while(1){
    std::cout << "Enter a Word: ";
        if(!std::getline(std::cin,userWord)){
        break; /* i/o error! */
        }
    if(userWord.empty()){
        break;
    }

   std::transform(userWord.begin(), userWord.end(), userWord.begin(),toupper);

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

void Boggle::shuffleCubes(Grid<char> &board,std::vector<std::string> &cubesVec){

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


bool Boggle::checkLength(std::string playerWord){
    if(playerWord.length()<MINIMUM_WORD_LENGTH){
        std::cout <<"That word doesn't meet the minimum word length."<<std::endl;
        return false;
    }
        return true;
}

bool Boggle::checkWordUsed(std::string playerWord,std::set<std::string>& usedWords){

    if(std::find(usedWords.begin(),usedWords.end(),playerWord)!=usedWords.end()){
        std::cout<<	"You've already found that word!"<<std::endl;
        return false;
    }
        return true;
}

bool Boggle::isEnglishWord(std::string playerWord){

    if(!englishWords.contains(playerWord)){
        std::cout <<"That's not a word!"<<std::endl;
        return false;
    }
    return true;
}

void Boggle::highlightWordPath(std::vector<GridPoint>& wordPath){
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


 bool Boggle::checkIfValidGuess(std::string playerWord,Grid<char>&board){

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


bool Boggle::boggleSolver(Grid<char>& board,int row,int col,std::string playerWord,unsigned int wordIndex,std::vector<GridPoint> &path,std::set<GridPoint> &usedSquares){

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



void Boggle::computerTurn(Grid<char> board,std::set<std::string>& usedWords){

    std::set<GridPoint> usedSquares;
    std::string word ="";

    for(int row=0;row<BOARD_SIZE;row++){
        for(int col=0;col<BOARD_SIZE;col++){
            computerBoggleSolver(board,row,col,word,usedSquares,usedWords);
        }
    }
}


bool Boggle::computerBoggleSolver(Grid<char>& board,int row,int col,std::string compWord,std::set<GridPoint> &usedSquares,std::set<std::string>& usedWords){

        if(!board.inBounds(row,col)){//if board location is out-of-bounds go on to the next square
            return false;
        }
        GridPoint pt(row,col);
        if(usedSquares.find(pt)!=usedSquares.end())
                return false;
        //if(word.size()<3)
        //	return false;

        if(englishWords.containsPrefix(compWord)||compWord.size()<MINIMUM_WORD_LENGTH-1){
            usedSquares.insert(pt);
            compWord+=board[row][col];
            if(englishWords.contains(compWord)&&compWord.size()>MINIMUM_WORD_LENGTH-1
                &&std::find(usedWords.begin(),usedWords.end(),compWord)==usedWords.end()){
                    usedWords.insert(compWord);
                    recordWordForPlayer(compWord, COMPUTER);
            }

        for(int i=0;i<sizeof(rdelta)/sizeof(rdelta[0]);i++){
            if(!englishWords.containsPrefix(compWord))
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
