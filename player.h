#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

// Playerdata
class Player {
    public:
        Player(): name(""), level(0), initiative(0), attack(0), defense(0), lifepoints(0), score(0) { }
    private:
        std::string name;
        int level;
        int initiative;
        int attack;
        int defense;
        int lifepoints;
        int score;
};

#endif
