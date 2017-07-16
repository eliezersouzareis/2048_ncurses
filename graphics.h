#ifndef _LIBS_H_
# include "libs.h"
#endif

#ifndef _GAME_H_
# include "game.h"
#endif

#ifndef _SCOREBOARD_H_
# include "scoreBoard.h"
#endif

#ifndef _GRAPHICS_H_
# define _GRAPHICS_H_

# ifndef _TLDEF_ // terminal lines default
#  define _TLDEF_ 24
# endif

# ifndef _TCDEF_ // terminal col default
#  define _TCDEF_ 80
# endif

void
initCursesMode();
void
endCursesMode();
void
activateCursor();
void
deactivateCursor();
WINDOW *
createWindow(int bh, int bw, int posy, int posx);
void
closeWindow(WINDOW * win, int bh, int bw);
void
clearWindow(WINDOW * win, int bh, int bw);
void
initColorPairs();
void
printHeader();
void
printFooter(char * filename);
WINDOW **
createBoard();
void printBoard(WINDOW * *cells, unsigned int board[][_BSIZE_]);
void
destroyBoard(WINDOW ** cells);
void
printScore(unsigned int * totalScore, unsigned int * score);
void
showHelp();
void
showScoreboard();
void
showMessage(int result, unsigned int * totalScore);
void
saveScoreWindow(unsigned int * totalScore);

void menu(int * ch, WINDOW * *boardCellsWindow, unsigned int board[][_BSIZE_], unsigned int * totalScore,
  unsigned int * score, char * filename);
void initGame(WINDOW * *boardCellsWindow, unsigned int board[][_BSIZE_], unsigned int * totalScore,
  unsigned int * score);
void printScreen(WINDOW * *boardCellsWindow, unsigned int board[][_BSIZE_], unsigned int * totalScore,
  unsigned int * score, char * filename);
void showSaveGameWindow(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score,
  char * filename);
void showLoadGameWindow(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score,
  char * filename);


#endif // ifndef _GRAPHICS_H_
