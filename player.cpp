#include "player.h"

std::string Player::get_name() {
    return this->name;
}
void Player::set_name(const std::string name) {
    this->name = name;
}

std::string Player::get_race() {
    return this->race;
}
void Player::set_race(const std::string race) {
    this->race = race;
}

int Player::get_level() {
    return this->level;
}
void Player::set_level(int level) {
    this->level = level;
}

int Player::get_initiative() {
    return this->initiative;
}
void Player::set_initiative(int initiative) {
    this->initiative = initiative;
}

int Player::get_attack() {
    return this->attack;
}
void Player::set_attack(int attack) {
    this->attack = attack;
}

int Player::get_defense() {
    return this->defense;
}
void Player::set_defense(int defense) {
    this->defense = defense;
}

int Player::get_lifepoints() {
    return this->lifepoints;
}
void Player::set_lifepoints(int lifepoints) {
    this->lifepoints = lifepoints;
}

int Player::get_score() {
    return this->score;
}
void Player::set_score(int score) {
    this->score = score;
}
