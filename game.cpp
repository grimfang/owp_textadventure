#include "game.h"

using namespace std;

vector<string> split(string &s, char delim) {
    vector<string> elems;
    if(s[s.size()-1] == ':') {
        s += " ";
    }
    stringstream ss(s, ios_base::in);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

int Game::show() {
    string character;
    cout << "starting game..." << endl << "loading races..." << endl;

    vector<string> race_names;
    vector<Player*> playable_chars;
    string line;
    Player* current_char = new Player();
    ifstream charfile ("characters.txt");
    if (charfile.is_open()) {
        while (getline (charfile, line)) {
            if(line.empty()) {
                playable_chars.push_back(current_char);
                current_char = new Player();
                continue;
            }
            vector<string> values = split(line, ':');
            if(values[0] == "species") {
                race_names.push_back(values[1]);
                current_char->set_race(values[1]);
            } else if(values[0] == "initiative") {
                current_char->set_initiative(stoi(values[1]));
            } else if(values[0] == "attack") {
                current_char->set_attack(stoi(values[1]));
            } else if(values[0] == "defense") {
                current_char->set_defense(stoi(values[1]));
            } else if(values[0] == "lifepoints") {
                current_char->set_lifepoints(stoi(values[1]));
            }
        }
        charfile.close();
    } else {
        cerr << "Unable to open character file";
        return unknownState;
    }

    cout << endl << endl;
    cout << "please select one of:" << endl;
    for(unsigned int i = 0; i < race_names.size(); i++) {
        cout << i << " " << race_names[i] << " | ";
    }
    cout << endl;
    cout << "please enter the number of the character you want to choose:";
    cin >> character;

    int charID = stoi(character);
    current_char = playable_chars[charID];

    cout << "You'll play as: " << current_char->get_race() << endl;
    cout << "please enter your name: ";
    string charName;
    cin >> charName;
    current_char->set_name(charName);

    cout << endl << "loading story..." << endl;
    cout << endl << endl << endl;
    map<int, string> story;
    map<int, vector<string>> decissions;
    map<int, Player*> enemies;
    ifstream storyfile ("story.txt");
    if (storyfile.is_open()) {
        int current_id = 0;
        while (getline (storyfile, line)) {
            if(line.empty()) {
                continue;
            }
            vector<string> values = split(line, ':');
            if(values[0] == "selection") {
                vector<string> selections = split(values[1], '|');
                decissions[current_id] = selections;
            } else if(values[0] == "enemy") {
                vector<string> enemy_values = split(values[1], '|');
                Player* enemy = new Player;
                enemy->set_name(enemy_values[0]);
                enemy->set_initiative(stoi(enemy_values[1]));
                enemy->set_attack(stoi(enemy_values[2]));
                enemy->set_defense(stoi(enemy_values[3]));
                enemy->set_lifepoints(stoi(enemy_values[4]));
                enemies[current_id] = enemy;
            } else {
                current_id = stoi(values[0]);
                if(values[1].empty()) values[1] = " ";
                story[current_id] += values[1] + "\n";
            }
        }
        storyfile.close();
    } else {
        cerr << "Unable to open story file";
        return unknownState;
    }

    bool end = false;
    unsigned int current_story_point = 0;
    do {
        cout << story.at(current_story_point);
        try {
            Player* enemy = enemies.at(current_story_point);
            cout << "enemy " << enemy->get_name() << " appeared" << endl;
            bool fightDone = false;
            bool playerTurn = false;
            bool playerWin = false;
            if (enemy->get_initiative() < current_char->get_initiative()) {
                playerTurn = true;
            }
            string action;
            int newPoints = 0;
            int damage = 0;
            while(!fightDone) {
                if (playerTurn) {
                    cout << "0) Attack    1) Flee" << endl;
                    cout << "> ";
                    cin >> action;
                    cin.get();
                    int selection = stoi(action);
                    switch (selection) {
                        case 0:
                            newPoints = 0;
                            damage = current_char->get_attack() - enemy->get_defense();
                            if (damage <= 0) damage = 1;
                            newPoints = enemy->get_lifepoints() - damage;
                            enemy->set_lifepoints(newPoints);
                            cout << "enemy lifepoints left: " << newPoints << endl;
                            if (newPoints <= 0) {
                                fightDone = true;
                                playerWin = true;
                            }
                            break;
                        case 1:
                            srand (time(NULL));
                            if (current_char->get_initiative() > enemy->get_initiative()) {
                                fightDone = true;
                                playerWin = true;
                            } else if(rand() % 2 == 1) {
                                fightDone = true;
                                playerWin = true;
                            }
                            if (fightDone) {
                                cout << "you can flee from the fight" << endl;
                            } else {
                                cout << "you can not flee from the fight" << endl;
                            }
                            break;
                    }
                    playerTurn = false;
                } else {
                    cout << enemy->get_name() << " attacks..." << endl;
                    newPoints = 0;
                    damage = enemy->get_attack() - current_char->get_defense();
                    if (damage <= 0) damage = 1;
                    newPoints = current_char->get_lifepoints() - damage;
                    cout << "player lifepoints left: " << newPoints << endl;
                    if (newPoints <= 0) {
                        fightDone = true;
                    }
                    current_char->set_lifepoints(newPoints);
                    playerTurn = true;
                }
            }
            if (!playerWin) {
                end = true;
                break;
            } else {
                cout << "you've won the fight" << endl;
                current_char->set_score(current_char->get_score() + 1);
                cout << "your current score: " << current_char->get_score() << endl;
            }
        } catch (out_of_range e) {
            //nothing to do here
        }

        bool has_decissions = false;
        try {
            map<int, int> display_decissions;
            int number_decissions = 0;
            for(unsigned int i = 0; i < decissions[current_story_point].size(); i++) {
                vector<string> decs = split(decissions[current_story_point][i], '>');
                display_decissions[i] = stoi(decs[1]);
                cout << i << ") " << decs[0] << "    ";
                has_decissions = true;
                number_decissions = i;
            }
            if (has_decissions) {
                string user_input;
                int choice;
                cout << endl;
                cout << "> ";
                cin >> user_input;
                cin.get();
                if (choice > number_decissions) choice = 0;
                else if (choice < number_decissions) choice = 0;
                choice = stoi(user_input);
                current_story_point = display_decissions[choice];
            }
        } catch (out_of_range e) {
            //nothing to do here
        }

        if (!has_decissions) {
            current_story_point += 1;
            cout << "press enter to continue" << endl;
            cin.get();
        }

        if(current_story_point >= story.size()) {
            end = true;
        }
    } while(!end);
    cout << endl << endl << "Final score: " << current_char->get_score() \
        << endl << endl << "Thanks for playing... " << current_char->get_name() \
        << endl << endl;
    return menuState;
}
