#include "game.h"

using namespace std;

vector<string> split(string &s, char delim) {
    /// splits the given string by the delimiter in delim and returns
    /// the resulting parts of that string.
    vector<string> elems;
    if(s[s.size()-1] == ':') {
        s += " ";
    }
    stringstream ss(s, ios_base::in);
    string item;
    // go through the string and pack all elements into the elems variable
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

int Game::show() {
    /// The main function of this game that will display the story as
    /// well as handle user input and the general game logic
    string character;
    cout << "starting game..." << endl << "loading races..." << endl;

    // add variables that will hold player data
    vector<string> race_names;
    vector<Player*> playable_chars;
    string line;
    Player* current_char = new Player();
    // open the characters file
    ifstream charfile ("characters.txt");
    if (charfile.is_open()) {
        // read in all lines of that file
        while (getline (charfile, line)) {
            // check if the line is empty
            if(line.empty()) {
                // add the current character to the list and start
                // reading a new one
                playable_chars.push_back(current_char);
                current_char = new Player();
                // move to the next line
                continue;
            }
            // split the current line and set the resulting values in
            // the current active character
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
        // close the file again
        charfile.close();
    } else {
        cerr << "Unable to open character file";
        return unknownState;
    }

    // add some space and as the player which character he wants to use
    cout << endl << endl;
    cout << "please select one of:" << endl;
    for(unsigned int i = 0; i < race_names.size(); i++) {
        cout << i << " " << race_names[i] << " | ";
    }
    cout << endl;
    cout << "please enter the number of the character you want to choose:";
    cin >> character;

    // set the character dependent on the players selection
    int charID = stoi(character);
    current_char = playable_chars[charID];

    // tell the player which character he choosed and ask him for a name
    cout << "You'll play as: " << current_char->get_race() << endl;
    cout << "please enter your name: ";
    string charName;
    cin >> charName;
    current_char->set_name(charName);

    // load the story file
    cout << endl << "loading story..." << endl;
    cout << endl << endl << endl;
    // some variables to store the story parts
    map<int, string> story;
    map<int, vector<string>> decissions;
    map<int, Player*> enemies;
    // now open the story textfile
    ifstream storyfile ("story.txt");
    if (storyfile.is_open()) {
        int current_id = 0;
        // read the lines of the text file
        while (getline (storyfile, line)) {
            if(line.empty()) {
                // ignore empty lines
                continue;
            }
            vector<string> values = split(line, ':');
            if(values[0] == "selection") {
                // read the possible selections
                vector<string> selections = split(values[1], '|');
                decissions[current_id] = selections;
            } else if(values[0] == "enemy") {
                // read in an enemy that will appear on the current part
                // of the story
                vector<string> enemy_values = split(values[1], '|');
                Player* enemy = new Player;
                enemy->set_name(enemy_values[0]);
                enemy->set_initiative(stoi(enemy_values[1]));
                enemy->set_attack(stoi(enemy_values[2]));
                enemy->set_defense(stoi(enemy_values[3]));
                enemy->set_lifepoints(stoi(enemy_values[4]));
                enemies[current_id] = enemy;
            } else {
                // add some story text parts
                current_id = stoi(values[0]);
                if(values[1].empty()) values[1] = " ";
                story[current_id] += values[1] + "\n";
            }
        }
        // close the story file
        storyfile.close();
    } else {
        cerr << "Unable to open story file";
        return unknownState;
    }

    // variable that will be used to check if the game is over
    bool end = false;
    unsigned int current_story_point = 0;
    do {
        cout << story.at(current_story_point);
        try {
            // use the try block to check if we have an enemy at the
            // current story position
            Player* enemy = enemies.at(current_story_point);
            // here we know we have an enemy
            cout << "enemy " << enemy->get_name() << " appeared" << endl;
            bool fightDone = false;
            bool playerTurn = false;
            bool playerWin = false;
            // check if the player hits first or if the enemy is fater
            if (enemy->get_initiative() < current_char->get_initiative()) {
                playerTurn = true;
            }
            string action;
            int newPoints = 0;
            int damage = 0;
            // start the fight
            while(!fightDone) {
                if (playerTurn) {
                    // output possible selections for the player
                    cout << "0) Attack    1) Flee" << endl;
                    cout << "> ";
                    // get and check the players selection
                    cin >> action;
                    cin.get();
                    int selection = stoi(action);
                    switch (selection) {
                        case 0:
                            // player attacks the enemy
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
                            // player tries to flee
                            srand (time(NULL));
                            if (current_char->get_initiative() > enemy->get_initiative()) {
                                // we are faster than the enemy and can flee instantly
                                fightDone = true;
                                playerWin = true;
                            } else if(rand() % 2 == 1) {
                                // we are lucky and got away from the fight
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
                    // set the playerTurn variable to false so the enemy
                    // will have the next turn
                    playerTurn = false;
                } else {
                    cout << enemy->get_name() << " attacks..." << endl;
                    newPoints = 0;
                    // calculate the damage that the enemy's attack will cause
                    damage = enemy->get_attack() - current_char->get_defense();
                    // do at least one damage point
                    if (damage <= 0) damage = 1;
                    // calculate the players new lifepoints
                    newPoints = current_char->get_lifepoints() - damage;
                    cout << "player lifepoints left: " << newPoints << endl;
                    if (newPoints <= 0) {
                        // the player has no lifepoints left, the fight
                        // is over
                        fightDone = true;
                    }
                    current_char->set_lifepoints(newPoints);
                    // set the next turn to be the player ones
                    playerTurn = true;
                }
            }
            if (!playerWin) {
                // the player lost the game
                end = true;
                break;
            } else {
                // the player won this fight and can continue
                cout << "you've won the fight" << endl;
                current_char->set_score(current_char->get_score() + 1);
                cout << "your current score: " << current_char->get_score() << endl;
            }
        } catch (out_of_range e) {
            //nothing to do here
        }

        bool has_decissions = false;
        try {
            // use the try block to check if we have decissions the
            // player can select from
            map<int, int> display_decissions;
            int number_decissions = 0;
            // display all the possible decissions
            for(unsigned int i = 0; i < decissions[current_story_point].size(); i++) {
                vector<string> decs = split(decissions[current_story_point][i], '>');
                display_decissions[i] = stoi(decs[1]);
                cout << i << ") " << decs[0] << "    ";
                has_decissions = true;
                number_decissions = i;
            }
            // now if we have decissions, ask the player to choose one
            // of the possible selections
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
                // move on to the selected point
                current_story_point = display_decissions[choice];
            }
        } catch (out_of_range e) {
            //nothing to do here
        }

        if (!has_decissions) {
            // only display the story and wait for the player to continue
            current_story_point += 1;
            cout << "press enter to continue" << endl;
            cin.get();
        }

        if(current_story_point >= story.size()) {
            // we reached the end of the story
            end = true;
        }
        // continue until we reache the end of the game
    } while(!end);
    // display some game statistics
    cout << endl << endl << "Final score: " << current_char->get_score() \
        << endl << endl << "Thanks for playing... " << current_char->get_name() \
        << endl << endl;
    // return to the menu
    return menuState;
}
