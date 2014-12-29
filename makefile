# all created object names need to be added here
objects = main.o menu.o options.o game.o

# the name of the executable
game_name = game

# using implicite rules, these flags will be used automatically
CPPFLAGS = -std=c++0x
game: $(objects)
	g++ -o $(game_name) $(objects)

main.o: states.h menu.h options.h game.h menu.o options.o game.o
menu.o: menu.h states.h
options.o: options.h states.h
game.o: game.h states.h

.PHONY : clean
clean:
	rm $(game_name) $(objects)
