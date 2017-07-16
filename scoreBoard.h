#ifndef _LIBS_H_
# include "libs.h"
#endif

#ifndef _SCOREBOARD_H_
# define _SCOREBOARD_H_

# ifndef _MAX_PLAYERS_
#  define _MAX_PLAYERS_ 10
# endif
// nome, data de nascimento, nacionalidade, endereço, email, pontuação e data que o jogador
struct _player {
    char         name[17];
    char         birthday[11];// "12/45/7890"
    char         nationality[4];// "BR"
    char         address[27];// cidade-estado
    char         email[27];
    char         data[11];
    unsigned int points;
};
typedef struct _player Player;

Player *
loadScoreBoard();
void
saveScoreBoard(Player * players);
void
sortScoreBoard(Player * players);
void
zeroScoreBoard(Player * players);
void
savePlayerScoreBoard(Player * player, unsigned int totalScore);
#endif // ifndef _SCOREBOARD_H_
