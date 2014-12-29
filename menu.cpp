#include <iostream>
#include "menu.h"
#include "states.h"

using namespace std;

int Menu::show() {
    cout << "Welcome to the World of ..." << endl << endl\
        << "1) Start Game" << endl \
        << "2) Options" << endl \
        << "3) Quit Game" << endl;

    string selection;
    cout << "choose: ";
    cin >> selection;


    if (selection == "1" or selection == "start" or selection == "s" or selection == "start game") {
        return gameState;
    } else if (selection == "2" or selection == "options" or selection == "o") {
        return optionsState;
    } else if (selection == "3" or selection == "quit" or selection == "q" or selection == "quit game") {
        return exitState;
    } else {
        return unknownState;
    }
}
