# all created object names need to be added here
objects = main.o menu.o options.o game.o player.o

# the name of the executable
game_name = game

# using implicite rules, these flags will be used automatically
CPPFLAGS = -std=c++0x -Wall -pedantic -Weffc++ -Werror
game: $(objects)
	g++ -o $(game_name) $(objects)

# create object files with implicite rules by just giving all the
# required header and object files
main.o: states.h menu.h options.h game.h menu.o options.o game.o
menu.o: menu.h states.h
options.o: options.h states.h
game.o: game.h player.h states.h player.o
player.o: player.h

# default clean method
.PHONY : clean
clean:
	rm $(game_name) $(objects)
