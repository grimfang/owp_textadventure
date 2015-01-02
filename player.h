#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

// Playerdata
class Player {
    public:
        Player(): name(""), race(""), level(0), initiative(0), attack(0), defense(0), lifepoints(0), score(0) { }
        std::string get_name();
        void set_name(const std::string name);

        std::string get_race();
        void set_race(const std::string race);

        int get_level();
        void set_level(int level);

        int get_initiative();
        void set_initiative(int initiative);

        int get_attack();
        void set_attack(int attack);

        int get_defense();
        void set_defense(int defense);

        int get_lifepoints();
        void set_lifepoints(int lifepoints);

        int get_score();
        void set_score(int score);

    private:
        std::string name;
        std::string race;
        int level;
        int initiative;
        int attack;
        int defense;
        int lifepoints;
        int score;
};

#endif
