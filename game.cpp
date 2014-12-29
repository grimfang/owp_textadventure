#include <iostream>
#include "game.h"
#include "states.h"

using namespace std;

int Game::show() {
    cout << "start game" << endl;
    return menuState;
}
