#ifndef STATES_H
#define STATES_H

// Game states
enum states {
    menuState = 0,
    gameState,
    optionsState,
    exitState,
    unknownState,
};

// States for the story (Currently unused)
enum story_states {
    storyTravel = 0,
    storyFight,
    storyLevelUp,
    storyExit,
};

#endif
