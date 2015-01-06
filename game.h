#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "states.h"
#include "player.h"

class Game {
    public:
        Game(): p() { }
        int show();
    private:
        Player p;
};

#endif
