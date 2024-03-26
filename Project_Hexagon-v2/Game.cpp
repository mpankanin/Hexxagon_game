//
// Created by panka on 03.01.2023.
//

#include "Game.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "String"

Game::Game(){
    counter = 0;
    pearlsResult = 3;
    rubiesResult = 3;
}

void Game::print() {
    using namespace std;

    for (size_t i{0}; i < 17; ++i) {
        for (size_t j{0}; j < 9; ++j) {
            if (boardArr[i][j] == Options::B)
                cout << "   ";
            else if (boardArr[i][j] == Options::E)
                cout << " 0 ";
            else if (boardArr[i][j] == Options::F)
                cout << " X ";
            else if (boardArr[i][j] == Options::P)
                cout << " P ";
            else
                cout << " R ";
        }
        cout << '\n';
    }

    cout << "Pearls: " << pearlsResult << "\nRubies: " << rubiesResult << endl;
}

void Game::fillSquare(Field field, const size_t& row, const size_t& column){

    if(field.getActionChar() == 'M') {
        if (counter % 2 == 0) {
            boardArr[field.getX()][field.getY()] = Options::P;
            ++pearlsResult;
        }
        else {
            boardArr[field.getX()][field.getY()] = Options::R;
            ++rubiesResult;
        }
    }else{
        if (counter % 2 == 0) {
            boardArr[field.getX()][field.getY()] = Options::P;
            boardArr[row][column] = Options::E;
        }else {
            boardArr[field.getX()][field.getY()] = Options::R;
            boardArr[row][column] = Options::E;
        }
    }
    aroundPawnChange(field.getX(), field.getY());
}

void Game::changeResults(Game::Options playerColor) {
    if(playerColor == Options::R){
        ++rubiesResult;
        --pearlsResult;
    } else{
        ++pearlsResult;
        --rubiesResult;
    }
}

bool Game::inBounds(int iRow, int iColumn) {
    return (iRow >= 0 && iRow <= 16) && (iColumn >= 0 && iColumn <=8);
}

void Game::aroundPawnChange(int iRow, int iColumn) {

    Options player, opponent;

    if (counter % 2 == 0) {
        player = Options::P;
        opponent = Options::R;
    } else {
        player = Options::R;
        opponent = Options::P;
    }

    for (int i{iRow - 2}; i <= (iRow + 2); ++i)
        for (int j{iColumn - 1}; j <= (iColumn + 1); ++j)
            if (inBounds(i, j) && boardArr[i][j] == opponent) {
                boardArr[i][j] = player;
                changeResults(player);
            }
}

bool Game::availableMovesCheck(size_t row, size_t column) {
    using namespace std;

    vector<Field> possibleMoves;


    int iRow = int(row);
    int iColumn = int(column);

    for(int i {iRow-3}; i <= (iRow+3); ++i)
        for(int j {iColumn-2}; j <= (iColumn+2); ++j)
            if(inBounds(i, j) && boardArr[i][j] == Options::E)
                possibleMoves.emplace_back(i, j);

    if(boardArr[iRow-4][iColumn] == Options::E)
        possibleMoves.emplace_back(iRow - 4, iColumn);
    if(boardArr[iRow+4][iColumn] == Options::E)
        possibleMoves.emplace_back(iRow + 4, iColumn);


    return !possibleMoves.empty();
}

void Game::availableMovesPrint(size_t row, size_t column, std::vector<Field>& availableMoves, std::vector<Field>& availableJumps) {
    using namespace std;

    int iRow = int(row);
    int iColumn = int(column);


    for (int i {iRow-2}; i <= (iRow+2); ++i)
        for (int j{iColumn - 1}; j <= (iColumn + 1); ++j)
            if (inBounds(i, j) && boardArr[i][j] == Options::E)
                availableMoves.emplace_back(i, j);


    for(int i {iRow-3}; i <= (iRow+3); ++i)
        for(int j {iColumn-2}; j <= (iColumn+2); ++j)
            if(inBounds(i, j) && boardArr[i][j] == Options::E)
                availableJumps.emplace_back(i, j);

    if(boardArr[iRow-4][iColumn] == Options::E)
        availableJumps.emplace_back(iRow - 4, iColumn);
    if(boardArr[iRow+4][iColumn] == Options::E)
        availableJumps.emplace_back(iRow + 4, iColumn);


    for(int i {0}; i < availableMoves.size(); ++i){
        for(int j {0}; j < availableJumps.size(); ++j)
            if(availableJumps[j].getX() == availableMoves[i].getX() &&
               availableJumps[j].getY() == availableMoves[i].getY())
                availableJumps.erase(availableJumps.begin() + j);
    }


    cout << "Moves: ";
    for(size_t i {0}; i < size(availableMoves); ++i)
        cout << '(' << availableMoves[i].getX() << ',' << availableMoves[i].getY() << ')';
    cout << '\n';

    cout << "Jumps: ";
    for(size_t i {0}; i < size(availableJumps); ++i)
        cout << '(' << availableJumps[i].getX() << ',' << availableJumps[i].getY() << ')';
    cout << '\n';

}

bool Game::pearlsAndRubiesCanMove() {
    using namespace std;

    bool pearlsCanMove = false;
    bool rubiesCanMove = false;

    for(size_t i {0}; i < 17 ; ++i){
        for(size_t j {0}; j < 9 ; ++j){
            if(boardArr[i][j] == Options::P && availableMovesCheck(i, j))
                pearlsCanMove = true;
            if(boardArr[i][j] == Options::R && availableMovesCheck(i, j))
                rubiesCanMove = true;
        }
    }


    return pearlsCanMove && rubiesCanMove;
}

bool Game::checkGameNotOver(){
    return counter < maxTurnsSize && pearlsAndRubiesCanMove();
}

Field Game::selectMove(std::vector<Field> &field, char action) {
    using namespace std;

    int inputRow;
    int inputColumn;
    bool correctNumber = false;

    while(!correctNumber) {
        cout << "Input row and column separated by enter key." << endl;
        inputRow = getInt(); cout << "Enter column: " << endl;
        inputColumn = getInt();
        for (size_t i{0}; i < field.size(); ++i) {
            if(field[i].getX() == inputRow && field[i].getY() == inputColumn)
                correctNumber = true;
        }
        cout << "Values out of possible coordinates, try again" << endl;
    }

    return {inputRow, inputColumn, action};
}

Field Game::actionSelector(std::vector<Field> &availableMoves, std::vector<Field> &availableJumps) {
    using namespace std;

    char action = 'A';

    if(!availableMoves.empty() && !availableJumps.empty()){
        while( action != 'M' && action != 'J' ){
            cout << "Select action you'd like to do: M - move, J - jump" << endl;
            cin >> action;
            if(action == 'm' || action == 'j')
                action = (char) toupper(action);
            while (cin.get() != '\n');
        }
    }else if (availableMoves.empty()){
        action = 'J';
    }else
        action = 'M';

    switch (action) {
        case 'M':
            return selectMove(availableMoves, 'M');
        case 'J':
            return selectMove(availableJumps, 'J');
        default:
            break;
    }


    return {0, 0};
}

size_t Game::selectRowPawn() {
    using namespace std;

    Options playerMark;
    vector<size_t> rowsAvalible;
    size_t row;
    int iRow;

    if(counter % 2 != 0) {
        playerMark = Options::R;
        cout << "Rubies turn!\nSelect row ( ";
    }
    else {
        playerMark = Options::P;
        cout << "Pearls turn!\nSelect row ( ";
    }

    for(size_t i {0}; i < 17; ++i){
        bool rowAvalible = false;
        for(size_t j {0}; j < 9; ++j){
            if(boardArr[i][j] == playerMark && availableMovesCheck(i, j))
                rowAvalible = true;
        }
        if(rowAvalible) {
            cout << i << ' ';
            rowsAvalible.push_back(i);
        }
    }
    cout << ')' << endl;

    bool incorrectNumber = true;
    while(incorrectNumber) {
        cout << "Input number: " << endl;
        iRow = getInt();
        row = static_cast<size_t>(iRow);
        for (size_t i {0}; i < size(rowsAvalible); ++i)
            if (row == rowsAvalible[i])
                incorrectNumber = false;
    }

    return row;
}

size_t Game::selectColumnPawn(size_t row){
    using namespace std;
    size_t column;
    int iColumn;
    vector<size_t> columnAvalible;
    Options playerMark;

    if(counter % 2 != 0)
        playerMark = Options::R;
    else
        playerMark = Options::P;

    cout << "Select column number ( ";
    for(size_t i = 0; i < 9; ++i){
        if(boardArr[row][i] == playerMark && availableMovesCheck(row, i)){
            cout << i << ' ';
            columnAvalible.push_back(i);
        }
    }
    cout << ')' << endl;

    bool incorrectNumber = true;
    while(incorrectNumber){
        cout << "Input number: " << endl;
        iColumn = getInt();
        column = static_cast<size_t>(iColumn);
        for(size_t i {0}; i < size(columnAvalible); i++)
            if(column == columnAvalible[i])
                incorrectNumber = false;
    }

    return column;
}

void Game::saveResults(int result) {
    using namespace std;

    if(result >= 10) {
        ofstream out;
        out.open("filein.txt", ios::app);

        string playerName;
        cout << "Insert winner name: " << endl;
        cin >> playerName;

        string str = to_string(result) + '\t' + playerName;
        out << str;
        out.close();
    }else
        cout << "Result under the highscore";
}

void Game::move() {
    using namespace std;

    vector<Field> avalibleMoves;
    vector<Field> avalibleJumps;

    const size_t x = selectRowPawn();
    const size_t y = selectColumnPawn(x);
    availableMovesPrint(x, y, avalibleMoves, avalibleJumps);
    fillSquare(actionSelector(avalibleMoves, avalibleJumps), x, y);


    ++counter;
}

void Game::printGameResult() {
    using namespace std;

    if(rubiesResult == pearlsResult) {
        cout << "DRAW !";
        saveResults(rubiesResult);
    }
    if(rubiesResult > pearlsResult) {
        cout << "RUBIES WON !";
        saveResults(rubiesResult);
    }
    if(pearlsResult > rubiesResult) {
        cout << "PEARLS WON !";
        saveResults(pearlsResult);
    }

}

void Game::ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int::Game::getInt(){
    while(true){
        int x {};
        std::cin >> x;

        if(!std::cin){
            std::cin.clear();
            ignoreLine();
            std::cerr << "Invalid value, try again" << std::endl;
        }else{
            ignoreLine();
            return x;
        }
    }
}



