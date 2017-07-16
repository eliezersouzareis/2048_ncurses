2048_ncurses: game.c main.c scoreBoard.c
	gcc game.c main.c graphics.c scoreBoard.c -o 2048_ncurses -Wall -lm -lncurses
