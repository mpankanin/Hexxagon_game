//
// Created by panka on 03.01.2023.
//

#ifndef PROJECT_HEXAGON_V2_GAME_H
#define PROJECT_HEXAGON_V2_GAME_H

#include "vector"
#include "Field.h"
#include "String"

/**
* Class containing general game utility.
*/
class Game {

    static const int rowsSize = 17;
    static const int columnsSize = 9;
    static const int maxTurnsSize = 58;

protected:

/**
     * Sets possible field options while game is running
     * P - Pearl, R - Rubie, B - Blanked, E - Empty, F - Forbidden.
     */
    enum class Options {P, R, B, E, F};

    /**
        * Game board based on 2 dimensional array which uses "options enum"
        * to prevent filling fields with unreconciled values.
        */
    Options boardArr[rowsSize][columnsSize] = {{Options::B, Options::B, Options::B, Options::B, Options::P, Options::B, Options::B, Options::B, Options::B},
                               {Options::B, Options::B, Options::B, Options::E, Options::B, Options::E, Options::B, Options::B, Options::B},
                               {Options::B, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::B},
                               {Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B},
                               {Options::R, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::R},
                               {Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B},
                               {Options::E, Options::B, Options::E, Options::B, Options::F, Options::B, Options::E, Options::B, Options::E},
                               {Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B},
                               {Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E},
                               {Options::B, Options::E, Options::B, Options::F, Options::B, Options::F, Options::B, Options::E, Options::B},
                               {Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E},
                               {Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B},
                               {Options::P, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::P},
                               {Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B},
                               {Options::B, Options::B, Options::E, Options::B, Options::E, Options::B, Options::E, Options::B, Options::B},
                               {Options::B, Options::B, Options::B, Options::E, Options::B, Options::E, Options::B, Options::B, Options::B},
                               {Options::B, Options::B, Options::B, Options::B, Options::R, Options::B, Options::B, Options::B, Options::B}};

    int counter;
    int pearlsResult;
    int rubiesResult;


public:

/// sets counter at zero value, and player result at 3.
    Game();

    /**
        * Prints actual board's array content.
        */
    void print ();

/**
     * Fills field with particular player's mark. Increasing and decreasing game results.
     * @param field to fill in.
     * @param row pawn coordinate.
     * @param column pawn coordinate.
     */
    void fillSquare(Field field, const size_t& row, const size_t& column);

    /**
     * Changes around enemy's pawns into player's - depending on game rules.
     * @param row pawn coordinate.
     * @param column pawn coordinate.
     */
    void aroundPawnChange(int iRow, int iColumn);

    /**
     * increments and decrements player's result depending on input color parameter.
     * @param color
     */
    void changeResults(Options color);

    /**
     * Checks if given coordinate is inside the board.
     * @param iRow pawn coordinate (int).
     * @param iColumn pawn coordinate (int).
     * @return bool value.
     */
    bool inBounds(int iRow, int iColumn);

    /**
     * Check if game isn't over.
     * @return bool value.
     */
    bool checkGameNotOver();

    /**
     * Checks if any pawn can move. Used to check if game is over.
     * @return bool value.
     */
    bool pearlsAndRubiesCanMove();

    /**
     * Checks if selected pawn have any possible moves.
     * @param row pawn coordinate.
     * @param column pawn coordinate.
     * @return bool type.
     */
    bool availableMovesCheck(size_t row, size_t column);

    /**
    * Prints available moves for selected pawn.
    * @param row pawn coordinate.
    * @param column pawn coordinate.
    * @param availableMoves Field's vector passed by reference to return it filled with possible moves.
    * @param availableJumps Field's vector passed by reference to return it filled with possible jumps.
    */
    void availableMovesPrint(size_t row, size_t column, std::vector<Field>& availableMoves, std::vector<Field>& availableJumps);

    /**
     * Takes field coordinates from user and checks if input data is correct.
     * @param field vector which contains available player's moves.
     * @param action wanted action move or jump.
     * @return Field object with action assigned.
     */
    static Field selectMove(std::vector<Field>& field, char action);

    /**
     * Takes and checks user action value.
     * M or m - move
     * J or j - jump
     * @param availableMoves possible moves vector.
     * @param availableJumps possible jumps vector.
     * @return selected by user field with particular action.
     */
    static Field actionSelector(std::vector<Field>& availableMoves, std::vector<Field>& availableJumps);

    /**
     * Prints rows with available moves. Input user's value and check if it fits with printed values.
     * @return correct row input by user.
     */
    size_t selectRowPawn();

    /**
     * Prints columns with available moves. Input user's value and checks if it fits with printed values.
     * @param row pawn coordinate.
     * @return correct column input by user.
     */
    size_t selectColumnPawn(size_t row);

    /**
     * Saves game result to highscore output file if result is bigger then 10.
     * @param result winner's game result.
     */
    static void saveResults(int result);

    /**
    * Moves pawns using particular methods.
    * Every move includes checking for available position,
    * changing opponent's pawns surrounding aim position
    * and incrementing counter field.
    */
    void move();

    /**
     * Compares player's results and prints them as the end game results and save them into a highscore when result is bigger then 10.
     */
    void printGameResult();

    /**
     * Ignores max range size of specific type, one by one until reach enter.
     */
    static void ignoreLine();

    /**
     * Protects input stream against invalid data.
     * @return correct int value
     */
    static int getInt();


};


#endif //PROJECT_HEXAGON_V2_GAME_H
