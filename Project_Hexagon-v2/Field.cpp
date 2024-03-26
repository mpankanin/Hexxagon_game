//
// Created by panka on 20.12.2022.
//

#include "Field.h"

Field::Field() {}

Field::Field(int x, int y) {
    this->x = x;
    this->y = y;
    action = 'A';
}

Field::Field(int x, int y, char c) {
    this->x = x;
    this->y = y;
    this->action = c;
}

int Field::getX() const {
    return x;
}

int Field::getY() const {
    return y;
}

char Field::getActionChar() const {
    return action;
}

void Field::setAction(char c) {
    this->action = c;
}
