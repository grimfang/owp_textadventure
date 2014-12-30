#ifndef OPTIONS_H
#define OPTIONS_H

struct options_struct {
    options_struct(int sw) : screenwidth(sw) { }
    int screenwidth;
};

// Default max width for text in the terminal
const int SCREENWIDTH_DEFAULT = 80;

class Options {
    public:
        options_struct options;
        Options() : options(SCREENWIDTH_DEFAULT) { }
        int show();
};

#endif

