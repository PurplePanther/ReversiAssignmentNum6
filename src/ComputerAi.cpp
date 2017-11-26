/******************************************
*Student name: Tal Pogorelis
*Student ID: 318225349
*Exercise #: 2
******************************************/


#include "ComputerAi.h"
#define MINVALUE -599

/**
 * The constructor method.
 * @param color - the player's color
 */
ComputerAi::ComputerAi(int color) : Player(color) {
    this->setAi(true);
}


/**
 * The function computes the Ai's next move.
 * @return - a Cell containing the X,Y values of the next move.
 */
Cell ComputerAi::chooseMove() {

    int x, y;
    Cell possibleMove;
    ReversiBoard* board = this->gameBoard;
    int currentplayer = this->color;
    ReversiBoard* tempBoard;
    ReversiBoard* secondTempBoard;

    int otherPlayersHighScoreMove;

    std::vector<Cell> possibleAIMoves = board->possibleMoves(currentplayer);
    std::vector<Cell> possibleEnemyPlayerMoves;
    std::vector<int> rankedEnemyMoves;
    std::vector<int> bestOfEnemyMoves;
    int i = 0;
    int j = 0;
    int xCounter = 0;
    std::vector<Cell>::iterator it;
    std::vector<int>::iterator intIt;
    std::vector<Cell>::iterator secondIterator;

    for (it = possibleAIMoves.begin(); it < possibleAIMoves.end(); i++,it++) {
        possibleMove = possibleAIMoves.at(i);

        tempBoard = new ReversiBoard(board->getSizeX(),board->getSizeY());
        tempBoard->copyBoard(board->getBoard());

        tempBoard->placePiece(currentplayer, possibleMove.getX()+1,possibleMove.getY()+1);
        //tempBoard->printBoard();

        j=0;
        possibleEnemyPlayerMoves = tempBoard->possibleMoves(((currentplayer-1)*-1));
        for ( secondIterator = possibleEnemyPlayerMoves.begin();
              secondIterator != possibleEnemyPlayerMoves.end() ; j++, secondIterator++) {

            otherPlayersHighScoreMove = MINVALUE;

            secondTempBoard = new ReversiBoard(board->getSizeX(),board->getSizeY());
            secondTempBoard->copyBoard(tempBoard->getBoard());

            secondTempBoard->placePiece(((currentplayer-1)*-1)
                    ,possibleEnemyPlayerMoves.at(j).getX()+1
                    ,possibleEnemyPlayerMoves.at(j).getY()+1);

            //secondTempBoard->printBoard();

            if(currentplayer == 1){
                if((secondTempBoard->countOCells() - secondTempBoard->countXCells()) >
                   otherPlayersHighScoreMove){
                    otherPlayersHighScoreMove = secondTempBoard->countOCells() -
                                                secondTempBoard->countXCells();
                }
            } else {
                if((secondTempBoard->countXCells() - secondTempBoard->countOCells()) >
                   otherPlayersHighScoreMove){
                    otherPlayersHighScoreMove = secondTempBoard->countXCells() -
                                                secondTempBoard->countOCells();
                }
            }

            rankedEnemyMoves.push_back(otherPlayersHighScoreMove);
            delete secondTempBoard;
        }


        int maxVal = rankedEnemyMoves.at(0);

        int placement = 0;

        xCounter = 0;
        for (intIt = rankedEnemyMoves.begin(); intIt != rankedEnemyMoves.end();
             xCounter++,intIt++) {
            if (maxVal < rankedEnemyMoves.at(xCounter)) {
                placement = xCounter;
                maxVal = rankedEnemyMoves.at(placement);
            }
        }
        bestOfEnemyMoves.push_back(maxVal);
        rankedEnemyMoves.clear();
        possibleEnemyPlayerMoves.clear();
        delete tempBoard;

    }

    int minVal = bestOfEnemyMoves.at(0);

    int placement = 0;
    xCounter = 0;

    for (intIt = bestOfEnemyMoves.begin(); intIt != bestOfEnemyMoves.end(); xCounter++,intIt++) {

        if (minVal > bestOfEnemyMoves.at(xCounter)) {
            placement = xCounter;
            minVal = bestOfEnemyMoves.at(placement);
        }

    }

    x = possibleAIMoves.at(placement).getX();
    y = possibleAIMoves.at(placement).getY();
    possibleAIMoves.clear();
    bestOfEnemyMoves.clear();
    Cell chosenXY = Cell(x+1,y+1);
    return chosenXY;

}
