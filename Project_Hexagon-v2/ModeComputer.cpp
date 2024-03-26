//
// Created by panka on 03.01.2023.
//

#include "ModeComputer.h"

ModeComputer::ModeComputer() {
    runGame();
}

void ModeComputer::runGame(){
    counter = 0;

    print();

    while(checkGameNotOver()){
        if(counter % 2 == 0)
            move();
        else
            computerMove();
        print();
    }

    printGameResult();
}

void ModeComputer::computerMove() {
    using namespace std;

    vector<Field> pawnsWithMoves;
    size_t index = 0;

    for (size_t i{0}; i < 17; ++i) {
        for (size_t j{0}; j < 9; ++j) {
            if (boardArr[i][j] == Options::R && availableMovesCheck(i, j))
                pawnsWithMoves.emplace_back(i, j);
        }
    }


    for(size_t i {0}; i < pawnsWithMoves.size(); ++i)
        if(countTheBestPossibleMove(pawnsWithMoves[i]) > countTheBestPossibleMove(pawnsWithMoves[index]))
            index = i;

    Field toMove = pawnsWithMoves[index];
    Field toField = retTheBestPossibleMove(pawnsWithMoves[index]);

    if(toField.getActionChar() == 'M') {
        boardArr[toField.getX()][toField.getY()] = Options::R;
        ++rubiesResult;
    }
    else{
        boardArr[toField.getX()][toField.getY()] = Options::R;
        boardArr[toMove.getX()][toMove.getX()] = Options::E;
    }

    aroundPawnChange(toField.getX(), toField.getY());




    ++counter;
}

size_t ModeComputer::countTheBestPossibleMove(Field field) {
    using namespace std;

    vector<Field> avalibleMoves;
    vector<Field> avalibleJumps;

    availableMovesPrintComp(field.getX(), field.getY(), avalibleMoves, avalibleJumps);

    size_t enemyPawnsMove = 0;
    for(size_t i {0}; i < avalibleMoves.size(); ++i){
        size_t tmp = 0;
        int iRow = int(avalibleMoves[i].getX());
        int iColumn = int(avalibleMoves[i].getY());
        for (int j {iRow-2}; j <= (iRow+2); ++j)
            for (int k {iColumn - 1}; k <= (iColumn + 1); ++k)
                if (boardArr[j][k] == Options::P)
                    ++tmp;
        if (tmp > enemyPawnsMove) {
            enemyPawnsMove = tmp;
        }
    }

    size_t enemyPawnsJump = 0;
    for(size_t i {0}; i < avalibleJumps.size(); ++i){
        size_t tmp = 0;
        int iRow = int(avalibleJumps[i].getX());
        int iColumn = int(avalibleJumps[i].getY());
        for (int j {iRow-2}; j <= (iRow+2); ++j)
            for (int k {iColumn - 1}; k <= (iColumn + 1); ++k)
                if (boardArr[j][k] == Options::P)
                    ++tmp;
        if (tmp > enemyPawnsJump) {
            enemyPawnsJump = tmp;
        }
    }

    size_t mostEfficientMove;

    if(enemyPawnsJump - enemyPawnsMove >= 2)
        mostEfficientMove = enemyPawnsJump;
    else
        mostEfficientMove = enemyPawnsMove;


    return mostEfficientMove;
}

Field ModeComputer::retTheBestPossibleMove(Field field) {
    using namespace std;

    vector<Field> avalibleMoves;
    vector<Field> avalibleJumps;

    availableMovesPrintComp(field.getX(), field.getY(), avalibleMoves, avalibleJumps);

    size_t enemyPawnsMove = 0;
    size_t enemyIndexMove = 0;
    for(size_t i {0}; i < avalibleMoves.size(); ++i){
        size_t tmp = 0;
        int iRow = int(avalibleMoves[i].getX());
        int iColumn = int(avalibleMoves[i].getY());
        for (int j {iRow-2}; j <= (iRow+2); ++j)
            for (int k {iColumn - 1}; k <= (iColumn + 1); ++k)
                if (boardArr[j][k] == Options::P)
                    ++tmp;
        if (tmp > enemyPawnsMove) {
            enemyPawnsMove = tmp;
            enemyIndexMove = i;
        }
    }

    size_t enemyPawnsJump = 0;
    size_t enemyIndexJump = 0;
    for(size_t i {0}; i < avalibleJumps.size(); ++i){
        size_t tmp = 0;
        int iRow = int(avalibleJumps[i].getX());
        int iColumn = int(avalibleJumps[i].getY());
        for (int j {iRow-2}; j <= (iRow+2); ++j)
            for (int k {iColumn - 1}; k <= (iColumn + 1); ++k)
                if (boardArr[j][k] == Options::P)
                    ++tmp;
        if (tmp > enemyPawnsJump) {
            enemyPawnsJump = tmp;
            enemyIndexJump = i;
        }
    }



    if(enemyPawnsJump - enemyPawnsMove >= 2){
        Field destField = avalibleJumps[enemyIndexJump];
        destField.setAction('J');
        return destField;
    }else{
        Field destField = avalibleMoves[enemyIndexMove];
        destField.setAction('M');
        return destField;
    }
}

void ModeComputer::availableMovesPrintComp(size_t row, size_t column, std::vector<Field>& availableMoves, std::vector<Field>& availableJumps) {
    using namespace std;

    int iRow = int(row);
    int iColumn = int(column);


    for (int i {iRow - 2}; i <= (iRow + 2); ++i)
        for (int j{iColumn - 1}; j <= (iColumn + 1); ++j)
            if (inBounds(i, j) && boardArr[i][j] == Options::E)
                availableMoves.emplace_back(i, j);


    for(int i {iRow - 3}; i <= (iRow + 3); ++i)
        for(int j {iColumn - 2}; j <= (iColumn + 2); ++j)
            if(inBounds(i, j) && boardArr[i][j] == Options::E)
                availableJumps.emplace_back(i, j);

    if(boardArr[iRow - 4][iColumn] == Options::E)
        availableJumps.emplace_back(iRow - 4, iColumn);
    if(boardArr[iRow + 4][iColumn] == Options::E)
        availableJumps.emplace_back(iRow + 4, iColumn);


    for(int i {0}; i < availableMoves.size(); ++i){
        for(int j {0}; j < availableJumps.size(); ++j)
            if(availableJumps[j].getX() == availableMoves[i].getX() &&
               availableJumps[j].getY() == availableMoves[i].getY())
                availableJumps.erase(availableJumps.begin() + j);
    }

}