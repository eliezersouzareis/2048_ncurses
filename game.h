#ifndef _LIBS_H_
# include "libs.h"
#endif

#ifndef _GAME_H_
# define _GAME_H_

# ifndef _BSIZE_
#  define _BSIZE_ 4
# endif

# ifndef __OBJWIN__
#  define __OBJWIN__ 2048 // 2048
# endif

unsigned int _OBJWIN_;

struct _gamestate {
    unsigned int board[_BSIZE_][_BSIZE_];
    unsigned int score;
    unsigned int totalScore;
    unsigned int gameOver;
};
typedef struct _gamestate GameState;

int randIsSeeded;

void
keepPlaying();
int
getRandomInt(int n);
void
swap(unsigned int * a, unsigned int * b);
unsigned int
sum(unsigned int * a, unsigned int * b);
void init(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score);
int gameOver(unsigned int board[][_BSIZE_]);
void newNumber(unsigned int board[][_BSIZE_]);
int canMoveUp(unsigned int board[][_BSIZE_]);
int canMoveRight(unsigned int board[][_BSIZE_]);
int canMoveDown(unsigned int board[][_BSIZE_]);
int canMoveLeft(unsigned int board[][_BSIZE_]);
int moveUp(unsigned int board[][_BSIZE_]);
int moveRight(unsigned int board[][_BSIZE_]);
int moveDown(unsigned int board[][_BSIZE_]);
int moveLeft(unsigned int board[][_BSIZE_]);
int getMovement(unsigned int board[][_BSIZE_], int ch);
int saveGame(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score, char * filename);
int loadGame(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score, char * filename);

#endif // ifndef _GAME_H_
