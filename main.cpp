
#include <iostream>
#include <stdlib.h>
#include "menu.h"
#include "options.h"
#include "game.h"
#include "states.h"

using namespace std;

int main(int argc, char **argv) {
    Menu menu = Menu();
    Options options = Options();
    Game game = Game();
    int state = menuState;
    do {
        switch (state) {
            case menuState:
                state = menu.show();
                break;
            case gameState:
                state = game.show();
                break;
            case optionsState:
                state = options.show();
                break;
            case exitState:
                cout << "exit game" << endl;
                exit(EXIT_SUCCESS);
                break;
            case unknownState:
                cout << "please select one of the menu entries" << endl;
                state = menuState;
                break;
            default:
                exit(EXIT_FAILURE);
                break;
        }
    } while (state != exitState);
	return EXIT_SUCCESS;
}
