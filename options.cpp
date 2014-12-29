#include <iostream>
#include <string>
#include <stdexcept>
#include "options.h"
#include "states.h"

using namespace std;

struct options {
    int screenwidth;
};

int Options::show() {
    options o;
    string text;
    int sw;
    cout << "::: Options :::" << endl;
    cout << "screen width (80): ";
    cin >> text;
    try {
        sw = stoi(text);
    } catch(invalid_argument e) {
        sw = 80;
    } catch(out_of_range e) {
        sw = 80;
    }
    cout << "set screenwidth to: " << sw << endl;
    o.screenwidth = sw;
    return menuState;
}
