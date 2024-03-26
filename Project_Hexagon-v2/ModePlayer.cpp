//
// Created by panka on 03.01.2023.
//

#include "ModePlayer.h"

ModePlayer::ModePlayer() {
    runGame();
}

void ModePlayer::runGame() {
    counter = 0;

    print();

    while(checkGameNotOver()){
        move();
        print();
    }

    printGameResult();
}
