//
// Created by panka on 20.12.2022.
//

#ifndef PROJECT_HEXAGON_V2_FIELD_H
#define PROJECT_HEXAGON_V2_FIELD_H

/**
 * Class containing field coordinates and action.
 */
class Field {

    int x;
    int y;
    char action;

public:

    int getX() const;
    int getY() const;
    char getActionChar() const;
    void setAction(char c);

    Field();
    Field(int x, int y);
    Field(int x, int y, char c);
};


#endif //PROJECT_HEXAGON_V2_FIELD_H
