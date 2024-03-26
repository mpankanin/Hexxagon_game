//
// Created by panka on 24.12.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "StartScreen.h"
#include "string"
#include "ModePlayer.h"
#include "ModeComputer.h"


StartScreen::StartScreen() {
    printStartScreen();
}

void StartScreen::selectGameMode() {
    using namespace std;
    char select;
    bool correctNumber = false;

    while(!correctNumber){
        cout << "Input command: " << endl;
        cin >> select;
        while(cin.get() != '\n');
        correctNumber = correctSelectChar(select);
    }

    select = (char)toupper(select);

    switch (select) {
        { case 'P':
                ModePlayer modePlayer;
            break;
        }{
            case 'C':
                ModeComputer modeComputer;
            break;
        }{
            case 'R':
                printTheBestResults();
                break;
        }{
            default:
                break;
        }
    }
}

bool StartScreen::correctSelectChar(char c) {
    return (c == 'P' || c == 'p') || (c == 'R' || c == 'r') || (c == 'C' || c == 'c');
}

void StartScreen::printStartScreen() {
    using namespace std;

    cout << "-----HEXXAGON GAME-----" << endl << endl;
    cout << "------SELECT MODE------" << endl;
    cout << "OR PRINT THE BEST PLAYER EVER RESULTS" << endl << endl << endl;
    cout << "PLAYER VS PLAYER   - COMMAND 'P'" << endl;
    cout << "PLAYER VS COMPUTER - COMMAND 'C'" << endl;
    cout << "RESULTS            - COMMAND 'R'" << endl;

}

void StartScreen::printTheBestResults() {
    using namespace std;


    ifstream infile("filein.txt");
    vector<std::string> v;
    string line;
    getline(infile, line);
    for (; getline(infile, line);)
        v.push_back(line);
    sort(v.begin(), v.end(), [](string s1, string s2) -> bool {
        return s1.substr(0, s1.find('\t')) > s2.substr(0, s2.find('\t'));
    });
    cout << "NUM  | RES | PLAYER NAME" << endl;
    if(v.size() >= 5)
        for (int i = 0; i < 5; i++)
            cout << i + 1 << '\t' << v[i] << endl;
    else if (v.empty())
        cout << "There aren't any results yet" << endl;
    else
        for (int i = 0; i < v.size(); i++)
            cout << i + 1 << '\t' << v[i] << endl;


    selectGameMode();
}



