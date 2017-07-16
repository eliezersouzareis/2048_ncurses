#include "scoreBoard.h"

Player *
loadScoreBoard()
{
    FILE * scoreFile;

    scoreFile = fopen("scoreboard.dat", "rb");
    Player * players = malloc(_MAX_PLAYERS_ * sizeof(Player));
    zeroScoreBoard(players);
    if (scoreFile != NULL) {
        // players= malloc(_MAX_PLAYERS_*sizeof(Player));
        fseek(scoreFile, 0, SEEK_END);
        size_t tamArq = ftell(scoreFile);
        rewind(scoreFile);
        fread(players, 1, tamArq, scoreFile);
        fclose(scoreFile);
    }
    return players;
}

void
saveScoreBoard(Player * players)
{
    FILE * scoreFile;

    scoreFile = fopen("scoreboard.dat", "wb");
    fwrite(players, sizeof(Player), _MAX_PLAYERS_, scoreFile);
    fclose(scoreFile);
}

void
playerSwap(Player * a, Player * b)
{
    Player c;

    memcpy(&c, b, sizeof(Player)); // b->c
    memcpy(b, a, sizeof(Player));  // a->b
    memcpy(a, &c, sizeof(Player)); // c->a
}

void
sortScoreBoard(Player * players)
{
    int i, j;
    int da, ma, aa, db, mb, ab;

    for (i = _MAX_PLAYERS_; i > 0; i--) {// bubble-sort
        for (j = 0; j < i - 1; j++) {
            if (players[j].points > players[j + 1].points) {
                playerSwap(&players[j], &players[j + 1]);
            } else if (players[j].points == players[j + 1].points) { // caso empate
                sscanf(players[j].birthday, "%d%*c%d%*c%d", &da, &ma, &aa); // interpreta data nasc
                sscanf(players[j + 1].birthday, "%d%*c%d%*c%d", &db, &mb, &ab);
                if (aa > ab) { // pa menor de idade que pb(anos)
                    playerSwap(&players[j], &players[j + 1]);
                } else if (aa == ab && ma > mb) { // pa nasceu mes sup que pb
                    playerSwap(&players[j], &players[j + 1]);
                } else if (aa == ab && ma == mb && da > db) { // pa nasceu dia sup que pb
                    playerSwap(&players[j], &players[j + 1]);
                }
            }
        }
    }
}

void
zeroScoreBoard(Player * players)
{
    int i;

    for (i = 0; i < _MAX_PLAYERS_; i++) {
        strcpy(players[i].name, "AAA");
        strcpy(players[i].birthday, " ");
        strcpy(players[i].nationality, "ND");
        strcpy(players[i].address, " ");
        strcpy(players[i].email, "aaa@aaa.aa");
        strcpy(players[i].data, " ");
        players[i].points = 0;
    }
}

void
savePlayerScoreBoard(Player * player, unsigned int totalScore)
{
    Player * players = loadScoreBoard();

    player->points = totalScore;
    time_t _now     = time(NULL);
    struct tm * now = localtime(&_now);
    sprintf(player->data, "%02d/%02d/%d", now->tm_mday, now->tm_mon, (now->tm_year + 1900));
    memcpy(&players[0], player, sizeof(Player));
    sortScoreBoard(players);
    saveScoreBoard(players);
}
