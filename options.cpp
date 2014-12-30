#include <iostream>
#include <string>
#include <stdexcept>
#include "options.h"
#include "states.h"

using namespace std;

int Options::show() {
    // options to be set
    string text;
    int screenwidth;

    // show the option values
    cout << "::: Options :::" << endl;

    // get the new value for screen width
    cout << "screen width (" << options.screenwidth << "): ";
    cin >> text;
    // Try to convert the user input to an integer or set it to 80 if
    // the value is not correct
    try {
        screenwidth = stoi(text);
    } catch(invalid_argument e) {
        screenwidth = SCREENWIDTH_DEFAULT;
    } catch(out_of_range e) {
        screenwidth = SCREENWIDTH_DEFAULT;
    }
    // give some feedback to the user
    cout << "set screenwidth to: " << screenwidth << endl;
    options.screenwidth = screenwidth;

    // return to the menu after all values are set
    return menuState;
}
