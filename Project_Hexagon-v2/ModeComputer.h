//
// Created by panka on 03.01.2023.
//

#ifndef PROJECT_HEXAGON_V2_MODECOMPUTER_H
#define PROJECT_HEXAGON_V2_MODECOMPUTER_H

#include "Game.h"

class ModeComputer: Game {

public:

    ModeComputer();


    /**
     * Runs a game in Player vs Computer mode.
     */
    void runGame();

    /**
     * Providing computer move connected with filling particular field and increasing and decreasing the game result.
     */
    void computerMove();

    /**
    * Analyses all computer's moves on given pawn and returns the most efficient move value.
    * @param field particular pawn.
    * @return the most efficient move value.
    */
    size_t countTheBestPossibleMove(Field field);

    /**
     * Analyses all computer's moves on given pawn and returns the most efficient move field.
     * @param field particular pawn.
     * @return the most efficient move field.
     */
    Field retTheBestPossibleMove(Field field);

    /**
     * Returns available moves and jumps for computer turn.
     * @param row pawn coordinate.
     * @param column pawn coordinate.
     * @param availableMoves Field's vector containing possible moves.
     * @param availableJumps Field's vector containing possible jumps.
     */
    void availableMovesPrintComp(size_t row, size_t column, std::vector<Field>& availableMoves, std::vector<Field>& availableJumps);

};


#endif //PROJECT_HEXAGON_V2_MODECOMPUTER_H
