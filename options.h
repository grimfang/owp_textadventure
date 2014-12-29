#ifndef OPTIONS_H
#define OPTIONS_H

struct options_struct {
    int screenwidth;
};

// Default max width for text in the terminal
const int SCREENWIDTH_DEFAULT = 80;

class Options {
    public:
        Options();
        options_struct options;
        int show();
};

#endif

