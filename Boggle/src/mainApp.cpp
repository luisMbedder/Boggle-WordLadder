
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

#include "boggle.h"
#include "console.h"


/********************************************************************
* Main program
********************************************************************/
int main() {

    Boggle *BoggleGame=new Boggle();

    while(true){
    BoggleGame->playBoggle();
    std::string result=BoggleGame->promptUser("Would you like to play again? ",1);
        if(result=="N")
            break;
    }

    return 0;
}
