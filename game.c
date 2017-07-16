#include "game.h"

int randIsSeeded = 0;

void
keepPlaying()
{
    _OBJWIN_ = 1;
}

int
getRandomInt(int n)
{
    if (randIsSeeded == 0) {
        srand(time(NULL));
        randIsSeeded = 1;
    }
    return rand() % n;
}

void
swap(unsigned int * a, unsigned int * b)
{
    int c;

    c  = *a;
    *a = *b;
    *b = c;
}

unsigned int
sum(unsigned int * a, unsigned int * b)
{
    *a += *b;
    *b  = 0;
    return *a;
}

void
init(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score)
{
    _OBJWIN_ = __OBJWIN__;
    // zera matriz
    unsigned int * p = &board[0][0], i;
    for (i = 0; i < _BSIZE_ * _BSIZE_; i++) {
        *p = 0;
        p++;
    }
    *totalScore = 0;
    *score      = 0;
    newNumber(board);
    newNumber(board);
}

int
gameOver(unsigned int board[][_BSIZE_])
{
    unsigned int * p = &board[0][0];
    int i, full = 1;

    for (i = 0; i < _BSIZE_ * _BSIZE_; i++) {
        if (*p == _OBJWIN_)
            return 1;

        if (*p == 0 && full == 1)
            full = 0;
        p++;
    }
    if (full) {
        if (canMoveUp(board) || canMoveLeft(board))
            return 0;

        return -1;
    }
    return 0;
}

void
newNumber(unsigned int board[][_BSIZE_])
{
    int x, y;

    do {
        x = getRandomInt(4);
        y = getRandomInt(4);
    } while (board[x][y]);
    if (getRandomInt(4) > 0) // enviesa a randomização para retornar mais 2 que 4
        board[x][y] = 2;
    else
        board[x][y] = 4;
}

int
canMoveUp(unsigned int board[][_BSIZE_])
{
    int lin, col, i;

    for (col = 0; col < _BSIZE_; col++) {
        for (lin = 0; lin < _BSIZE_ - 1; lin++) {
            i = lin + 1;
            while (i < _BSIZE_ - 1 && board[i][col] == 0) i++;
            if (board[lin][col] == board[i][col] && board[lin][col] != 0)
                return 1;

            if (board[lin][col] == 0 && board[i][col] != 0)
                return 1;
        }
    }
    return 0;
}

int
thenMoveUp(unsigned int board[][_BSIZE_])
{
    int lin, col, i;
    int score = 0;

    for (col = 0; col < _BSIZE_; col++) {
        for (lin = 0; lin < _BSIZE_ - 1; lin++) {
            i = lin + 1;
            while (i < _BSIZE_ - 1 && board[i][col] == 0) i++;
            if (board[lin][col] == board[i][col]) {
                score += sum(&board[lin][col], &board[i][col]);
            }
        }
        for (lin = 0; lin < _BSIZE_ - 1; lin++) {
            if (board[lin][col] == 0) {
                i = lin + 1;
                while (i < _BSIZE_ - 1 && board[i][col] == 0) i++;
                swap(&board[lin][col], &board[i][col]);
            }
        }
    }
    return score;
}

int
canMoveRight(unsigned int board[][_BSIZE_])
{
    int lin, col, i;

    for (lin = 0; lin < _BSIZE_; lin++) {
        for (col = _BSIZE_ - 1; col > 0; col--) {
            i = col - 1;
            while (i > 0 && board[lin][i] == 0) i--;
            if (board[lin][col] == board[lin][i] && board[lin][col] != 0)
                return 1;

            if (board[lin][col] == 0 && board[lin][i] != 0)
                return 1;
        }
    }
    return 0;
}

int
thenMoveRight(unsigned int board[][_BSIZE_])
{
    int lin, col, i;
    int score = 0;

    for (lin = 0; lin < _BSIZE_; lin++) {
        for (col = _BSIZE_ - 1; col > 0; col--) {
            i = col - 1;
            while (i > 0 && board[lin][i] == 0) i--;
            if (board[lin][col] == board[lin][i]) {
                score += sum(&board[lin][col], &board[lin][i]);
            }
        }
        for (col = _BSIZE_ - 1; col > 0; col--) {
            if (board[lin][col] == 0) {
                i = col - 1;
                while (i > 0 && board[lin][i] == 0) i--;
                swap(&board[lin][col], &board[lin][i]);
            }
        }
    }
    return score;
}

int
canMoveDown(unsigned int board[][_BSIZE_])
{
    int lin, col, i;

    for (col = 0; col < _BSIZE_; col++) {
        for (lin = _BSIZE_ - 1; lin > 0; lin--) {
            i = lin - 1;
            while (i > 0 && board[i][col] == 0) i--;
            if (board[lin][col] == board[i][col] && board[lin][col] != 0)
                return 1;

            if (board[lin][col] == 0 && board[i][col] != 0)
                return 1;
        }
    }
    return 0;
}

int
thenMoveDown(unsigned int board[][_BSIZE_])
{
    int lin, col, i;
    int score = 0;

    for (col = 0; col < _BSIZE_; col++) {
        for (lin = _BSIZE_ - 1; lin > 0; lin--) {
            i = lin - 1;
            while (i > 0 && board[i][col] == 0) i--;
            if (board[lin][col] == board[i][col]) {
                score += sum(&board[lin][col], &board[i][col]);
            }
        }
        for (lin = _BSIZE_ - 1; lin > 0; lin--) {
            if (board[lin][col] == 0) {
                i = lin - 1;
                while (i > 0 && board[i][col] == 0) i--;
                swap(&board[lin][col], &board[i][col]);
            }
        }
    }


    return score;
}

int
canMoveLeft(unsigned int board[][_BSIZE_])
{
    int lin, col, i;

    for (lin = 0; lin < _BSIZE_; lin++) {
        for (col = 0; col < _BSIZE_ - 1; col++) {
            i = col + 1;
            while (i < _BSIZE_ - 1 && board[lin][i] == 0) i++;
            // existe pelo menos uma soma
            if (board[lin][col] == board[lin][i] && board[lin][col] != 0)
                return 1;

            // existe pelo menos um espaço
            if (board[lin][col] == 0 && board[lin][i] != 0)
                return 1;
        }
    }
    return 0;
}

int
thenMoveLeft(unsigned int board[][_BSIZE_])
{
    int lin, col, i;
    int score = 0;

    for (lin = 0; lin < _BSIZE_; lin++) {
        // soma
        for (col = 0; col < _BSIZE_ - 1; col++) {
            i = col + 1;
            while (i < _BSIZE_ - 1 && board[lin][i] == 0) i++;
            if (board[lin][col] == board[lin][i]) {
                score += sum(&board[lin][col], &board[lin][i]);
            }
        }
        // comprime pro lado desejado
        for (col = 0; col < _BSIZE_ - 1; col++) {
            if (board[lin][col] == 0) {
                i = col + 1;
                while (i < _BSIZE_ - 1 && board[lin][i] == 0) i++;
                swap(&board[lin][col], &board[lin][i]);
            }
        }
    }

    return score;
}

int
getMovement(unsigned int board[][_BSIZE_], int ch)
{
    int score = 0, moved = 0;

    switch (ch) {
        case KEY_UP:
            if (canMoveUp(board)) {
                score = thenMoveUp(board);
                moved = 1;
            }
            break;
        case KEY_RIGHT:
            if (canMoveRight(board)) {
                score = thenMoveRight(board);
                moved = 1;
            }
            break;
        case KEY_DOWN:
            if (canMoveDown(board)) {
                score = thenMoveDown(board);
                moved = 1;
            }
            break;
        case KEY_LEFT:
            if (canMoveLeft(board)) {
                score = thenMoveLeft(board);
                moved = 1;
            }
            break;
    }
    if (moved) {
        newNumber(board);
    }
    return score;
} /* getMovement */

int
saveGame(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score, char * filename)
{
    FILE * gs = NULL;

    if (strlen(filename)) {
        gs = fopen(filename, "wb");
    } else {
        gs = fopen("lastGame.dat", "wb");
    }
    if (gs != NULL) {
        GameState * g = malloc(sizeof(GameState));
        memcpy(g->board, board, _BSIZE_ * _BSIZE_ * sizeof(unsigned int));
        g->score      = *score;
        g->totalScore = *totalScore;
        if (_OBJWIN_ == 1)
            g->gameOver = 1;
        else
            g->gameOver = 0;
        fwrite(g, sizeof(GameState), 1, gs);
        free(g);
        fclose(gs);
        return 1;
    }
    return 0;
}

int
loadGame(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score, char * filename)
{
    FILE * gs;

    if (strlen(filename)) {
        gs = fopen(filename, "rb");
    } else  {
        gs = fopen("lastGame.dat", "rb");
    }
    if (gs != NULL) {
        GameState * g = malloc(sizeof(GameState));
        fread(g, sizeof(GameState), 1, gs);
        // fwrite(g, sizeof(GameState), 1, gs);
        memcpy(board, g->board, _BSIZE_ * _BSIZE_ * sizeof(unsigned int));
        *score      = g->score;
        *totalScore = g->totalScore;
        if (g->gameOver) {
            _OBJWIN_ = 1;
        } else {
            _OBJWIN_ = __OBJWIN__;
        }
        free(g);
        fclose(gs);
        return 1;
    }
    init(board, totalScore, score);
    return 0;
}
