//
// Created by panka on 24.12.2022.
//

#ifndef PROJECT_HEXAGON_V2_STARTSCREEN_H
#define PROJECT_HEXAGON_V2_STARTSCREEN_H
#include "Algorithm"

/**
 * Class contains the main amenities of the start screen.
 */
class StartScreen {
public:

    StartScreen();

    /**
     * Gives user ability to choose game mode.
     */
    void selectGameMode();


    static void printStartScreen();

    /**
     * checks if values are: P, R, C, p, r, c.
     * @param c input char to check if char fits to mentioned range.
     * @return bool value.
     */
    static bool correctSelectChar(char c);


    /**
     * Printing the bast game results ever from specific file.
     */
    void printTheBestResults();

};


#endif //PROJECT_HEXAGON_V2_STARTSCREEN_H
