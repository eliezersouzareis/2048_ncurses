#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"


int
main(int argc, char const * argv[])
{
    unsigned int board[_BSIZE_][_BSIZE_];
    unsigned int totalScore = 0, score, aux;
    int i, j, k;

    for (i = 0; i < _BSIZE_; i++) {
        for (j = 0; j < _BSIZE_; j++) {
            do {
                printf("informe exponente posicao board[%d][%d]\n", i, j);
                scanf("%u", &aux);
            } while (aux < 0 || aux > 15);
            if (aux > 0) {
                if (aux >= 1) {
                    board[i][j] = 2;
                    score       = 0;
                    for (k = 0; k < aux; k++) {
                        board[i][j] *= 2;
                        score       += board[i][j];
                    }
                    totalScore += score;
                } else {
                    board[i][j] = 2;
                }
            } else   {
                board[i][j] = 0;
            }
            if (board[i][j] >= __OBJWIN__)
                _OBJWIN_ = 1;
        }
    }
    for (i = 0; i < _BSIZE_; i++) {
        for (j = 0; j < _BSIZE_; j++) {
            printf("%6d ", board[i][j]);
        }
        printf("\n");
    }
    char filename[32];
    printf("Informe nome do arquivo a ser salvo\n");
    scanf("%s", filename);
    strcat(filename, ".dat");

    saveGame(board, &totalScore, &score, filename);

    return 0;
} /* main */
