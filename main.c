#include "main.h"

int
main(int argc, char const * argv[])
{
    setlocale(LC_ALL, "");
    int ch;
    WINDOW ** boardCellsWindow;
    unsigned int board[_BSIZE_][_BSIZE_];
    unsigned int score, totalScore, gameRes = 0;
    char filename[32] = "lastGame.dat";
    initCursesMode();
    boardCellsWindow = createBoard();
    printHeader();
    // init(board,&score,&totalScore);
    loadGame(board, &totalScore, &score, filename);
    printScreen(boardCellsWindow, board, &totalScore, &score, filename);
    while ((ch = getch()) != 27) {
        menu(&ch, boardCellsWindow, board, &totalScore, &score, filename);
        score       = getMovement(board, ch);
        totalScore += score;
        printScreen(boardCellsWindow, board, &totalScore, &score, filename);
        if ((gameRes = gameOver(board))) {
            showMessage(gameRes, &totalScore);
            if (_OBJWIN_ % 2 == 0 || gameRes == -1) // se não vai continuar jogando
                initGame(boardCellsWindow, board, &totalScore, &score);
            printScreen(boardCellsWindow, board, &totalScore, &score, filename);// por causa de showMessage
        }
        refresh();
    }
    if (gameRes == -1) { // garantia que n vai copiar um jogo perdido
        init(board, &totalScore, &score);
    }
    saveGame(board, &totalScore, &score, filename);
    destroyBoard(boardCellsWindow);
    endCursesMode();
    return 0;
} /* main */
