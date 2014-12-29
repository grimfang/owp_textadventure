
#include <iostream>
#include <stdlib.h>
#include "menu.h"
#include "options.h"
#include "game.h"
#include "states.h"

using namespace std;

int main(int argc, char **argv) {
    // game state elements
    Menu menu = Menu();
    Options options = Options();
    Game game = Game();

    int state = menuState;
    // start the main loop
    do {
        // check the current state of the game
        switch (state) {
            case menuState:
                // Enter the menu state dialog
                state = menu.show();
                break;
            case gameState:
                // Start the main game part
                state = game.show();
                break;
            case optionsState:
                // Enter the options dialog
                state = options.show();
                break;
            case unknownState:
                // An unknown state, return to the main menu state
                cout << "please select one of the menu entries" << endl;
                state = menuState;
                break;
            default:
                // something else happened return to the main menu
                state = menuState;
                break;
        }
        //check if we got to the exit state
    } while (state != exitState);
    // output a note for the user that the game will be quit
    cout << "exit game" << endl;
    // quit with success
	return EXIT_SUCCESS;
}
