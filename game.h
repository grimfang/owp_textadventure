#ifndef GAME_H
#define GAME_H

#include <iostream>
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
