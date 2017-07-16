#include "graphics.h"

void
initCursesMode()
{
    initscr();        // inicia curses
    start_color();    // inicia cor
    initColorPairs(); // inicia os pares de cores usados
    cbreak();         // habilita ctrl-c
    // raw(); // desabilita ctrl-c
    keypad(stdscr, TRUE); // habilita function keys(f1,f2...)
    noecho();             // n ecoar letras digitadas
    curs_set(0);          // cursor invisivel
}

void
endCursesMode()
{
    endwin(); // finaliza curses
}

void
activateCursor()
{
    echo();
    curs_set(1);
}

void
deactivateCursor()
{
    noecho();    // n ecoar letras digitadas
    curs_set(0); // cursor invisivel
}

WINDOW *
createWindow(int bh, int bw, int posy, int posx)
{
    WINDOW * win;

    win = newwin(bh, bw, posy, posx);
    box(win, 0, 0);
    return win;
}

void
closeWindow(WINDOW * win, int bh, int bw)
{
    int i, j;

    for (i = 0; i < bh; i++) {
        for (j = 0; j < bw; j++) {
            mvwprintw(win, i, j, " ");
        }
    }
    wrefresh(win);
    delwin(win);
}

void
clearWindow(WINDOW * win, int bh, int bw)
{
    int i, j;

    for (i = 0; i < bh; i++) {
        for (j = 0; j < bw; j++) {
            mvwprintw(win, i, j, " ");
        }
    }
    box(win, 0, 0);
    wrefresh(win);
}

void
initColorPairs()
{
    short n = 1;

    init_pair(n++, COLOR_GREEN, COLOR_BLACK);// 2
    init_pair(n++, COLOR_GREEN, COLOR_BLACK);// 4
    init_pair(n++, COLOR_YELLOW, COLOR_BLACK);// 8
    init_pair(n++, COLOR_YELLOW, COLOR_BLACK);// 16
    init_pair(n++, COLOR_BLUE, COLOR_BLACK);// 32
    init_pair(n++, COLOR_BLUE, COLOR_BLACK);// 64
    init_pair(n++, COLOR_MAGENTA, COLOR_BLACK);// 128
    init_pair(n++, COLOR_MAGENTA, COLOR_BLACK);// 256
    init_pair(n++, COLOR_CYAN, COLOR_BLACK);// 512
    init_pair(n++, COLOR_CYAN, COLOR_BLACK);// 1024
    init_pair(n++, COLOR_RED, COLOR_BLACK);// 2048
    init_pair(n++, COLOR_RED, COLOR_BLACK);// 4096
}

void
printHeader() // imprime 2048 bonitinho
{
    int x = 0, y = 0;

    mvaddch(y, x++, ACS_ULCORNER);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_TTEE);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_TTEE);
    mvaddch(y, x++, ACS_TTEE);
    mvaddch(y, x++, ACS_TTEE);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_URCORNER);
    x = 0;
    y++;
    mvaddch(y, x++, ACS_LTEE);
    mvaddch(y, x++, ' ');
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_LTEE);
    mvaddch(y, x++, ' ');
    mvaddch(y, x++, ACS_RTEE);
    x = 0;
    y++;
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ' ');
    mvaddch(y, x++, ACS_RTEE);
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_LTEE);
    mvaddch(y, x++, ACS_URCORNER);
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_VLINE);
    mvaddch(y, x++, ACS_VLINE);
    x = 0;
    y++;
    mvaddch(y, x++, ACS_LLCORNER);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_BTEE);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_LRCORNER);
    mvaddch(y, x++, ACS_LLCORNER);
    mvaddch(y, x++, ACS_BTEE);
    mvaddch(y, x++, ACS_HLINE);
    mvaddch(y, x++, ACS_LRCORNER);
    // refresh();
} /* printHeader */

void
printFooter(char * filename) // imprime rodapé
{
    mvwprintw(stdscr, _TLDEF_ - 1, 0, "Jogo: %s                              ", filename);
    mvwprintw(stdscr, _TLDEF_, 0, "[F1]:Ajuda  [F2]:ScoreBoard  [F3]:Reset  [F4]:Salvar  [F5]:Carregar  [ESC]:Sair");
}

WINDOW **
createBoard() // cria uma série de janelas, posicionadas de acordo
{
    WINDOW ** cell = malloc(_BSIZE_ * _BSIZE_ * sizeof(WINDOW *));
    int i, j, k, x, y;
    int bh, bw;

    bh = 3;
    bw = 6; // box-height; box-width | tamanho das caixas /considerar utilizar constantes
    y  = 6;
    x  = 2; // posicionamento inicial  /considerar utilizar constantes
    for (i = 0; i < _BSIZE_; i++) {
        for (j = 0; j < _BSIZE_; j++) {
            k       = (i * _BSIZE_) + j; // CONHECE HASH?
            cell[k] = newwin(bh, bw, y, x);
            x      += bw;
        }
        x  = 2;
        y += bh;
    }
    refresh();
    return cell;
}

void
printBoard(WINDOW ** cells, unsigned int board[][_BSIZE_])
{
    int i, j, k, l;

    for (i = 0; i < _BSIZE_; i++) {
        for (j = 0; j < _BSIZE_; j++) {
            k = (i * _BSIZE_) + j; // HAAAAAAAAAAAASH
            if (board[i][j]) {
                l = log2(board[i][j]);// decide qual par de cor será utilizado com base no valor
                l = ((l - 1) % 12) + 1;
                if (l % 2) { // se parte inferior de um numero maior
                    wattron(cells[k], A_DIM | COLOR_PAIR(l)); // mais escuro
                } else {
                    wattron(cells[k], COLOR_PAIR(l)); // mais claro
                }

                box(cells[(k)], 0, 0);
                mvwprintw(cells[k], 1, 1, "%4u", board[i][j]);

                if (l % 2) { // desativa cor
                    wattroff(cells[k], A_DIM | COLOR_PAIR(l));
                } else {
                    wattroff(cells[k], COLOR_PAIR(l));
                }
            } else { // vazio
                wattron(cells[k], A_DIM);
                box(cells[k], 0, 0);
                mvwprintw(cells[k], 1, 1, "    ");
                wattroff(cells[k], A_DIM);
            }
            wrefresh(cells[k]);
        }
    }
    // refresh();
} /* printBoard */

void
destroyBoard(WINDOW ** cells)
{
    int i;

    for (i = 0; i < _BSIZE_ * _BSIZE_; i++) {
        delwin(cells[i]);
    }
}

void
printScore(unsigned int * totalScore, unsigned int * score)
{
    if (*score) {
        mvwprintw(stdscr, 4, 20, "SCORE: %10u +%u          ", *totalScore, *score);
    } else {
        mvwprintw(stdscr, 4, 20, "SCORE: %10u              ", *totalScore);
    }
}

void
showHelp()
{
    int ch;
    WINDOW * win;
    int bh = 9, bw = 41;

    win = createWindow(bh, bw, 7, 0);
    int l = 2;
    mvwprintw(win, 0, 2, "Ajuda - [ESC] para sair");
    mvwprintw(win, l++, 2, "[ ↑ ] - move numeros para cima");
    mvwprintw(win, l++, 2, "[ → ] - move numeros para direita");
    mvwprintw(win, l++, 2, "[ ↓ ] - move numeros para baixo");
    mvwprintw(win, l++, 2, "[ ← ] - move numeros para esquerda");
    wrefresh(win);
    while ((ch = getch()) != 27) ;
    closeWindow(win, 9, 41);
}

void
showScoreboard()
{
    int ch;
    WINDOW * win;
    int bh = 20, bw = _TCDEF_ + 26;

    win = createWindow(bh, bw, 4, 0);
    int l = 2, i, c;
    Player * players = loadScoreBoard();
    mvwprintw(win, 0, 2, "ScoreBoard - [ESC] para sair");
    c = 4;
    mvwprintw(win, l, c, "Nome");
    c += sizeof(players[0].name) - 1;
    mvwprintw(win, l, c, "Nasc.");
    c += sizeof(players[0].birthday);
    mvwprintw(win, l, c, "Nac.");
    c += sizeof(players[0].nationality);
    mvwprintw(win, l, c, "Email");
    c += sizeof(players[0].email);
    mvwprintw(win, l, c, "Data");
    c += sizeof(players[0].data);
    mvwprintw(win, l, c, "Pontos");
    c += 11;
    mvwprintw(win, l, c, "Endereço");
    for (i = _MAX_PLAYERS_ - 1; i >= 0; i--) {
        l++;
        c = 4;
        mvwprintw(win, l, 1, "%2d.", _MAX_PLAYERS_ - i);
        mvwprintw(win, l, c, "%s", players[i].name);
        c += sizeof(players[0].name) - 1;
        mvwprintw(win, l, c, "%s", players[i].birthday);
        c += sizeof(players[0].birthday);
        mvwprintw(win, l, c, "%s", players[i].nationality);
        c += sizeof(players[0].nationality);
        mvwprintw(win, l, c, "%s", players[i].email);
        c += sizeof(players[0].email);
        mvwprintw(win, l, c, "%s", players[i].data);
        c += sizeof(players[0].data);
        mvwprintw(win, l, c, "%llu", players[i].points);
        c += 11;
        mvwprintw(win, l, c, "%s", players[i].address);
    }
    wrefresh(win);

    while ((ch = getch()) != 27) { }
    closeWindow(win, bh, bw);
} /* showScoreboard */

void
showMessage(int result, unsigned int * totalScore)
{
    char msgWin[]  = "PARABÉNS! VOCÊ VENCEU!";
    char msgLoss[] = "QUE PENA! VOCÊ PERDEU!";
    char msgQuit[] = "pressione [space] para continuar";
    WINDOW * win;
    int ch;
    int bh = 3, bw = 41; // box-height; box-width

    win = createWindow(bh, bw, 11, 0);
    if (result == 1) {
        mvwprintw(win, 1, ((bw / 2) - (strlen(msgWin) / 2)), "%s", msgWin);
    } else {
        mvwprintw(win, 1, ((bw / 2) - (strlen(msgLoss) / 2)), "%s", msgLoss);
    }
    mvwprintw(win, 2, (bw - strlen(msgQuit)) - 1, "%s", msgQuit); // imprimir no canto
    wrefresh(win);
    while ((ch = getch()) != ' ') ;
    Player * ps = loadScoreBoard();
    if (*totalScore >= ps[0].points) {
        char question[] = "Deseja salvar seu score?(s/n)";
        mvwprintw(win, 1, ((bw / 2) - (strlen(question) / 2)), "%s", question);
        box(win, 0, 0);
        wrefresh(win);
        while ((ch = getch()) != 's' && ch != 'n') ;
        if (ch == 's') {
            saveScoreWindow(totalScore);
            showScoreboard();
        }
    }
    free(ps);
    if (result == 1) {
        clearWindow(win, bh, bw);
        char question2[] = "Continuar jogando este jogo?(s/n)";
        mvwprintw(win, 1, ((bw / 2) - (strlen(question2) / 2)), "%s", question2);
        wrefresh(win);
        while ((ch = getch()) != 's' && ch != 'n') ;
        if (ch == 's') {
            keepPlaying();
        }
    }
    closeWindow(win, bh, bw);
} /* showMessage */

void
saveScoreWindow(unsigned int * totalScore)
{
    WINDOW * win;
    int bh = 7, bw = 60; // box-height; box-width

    win = createWindow(bh, bw, 7, 0);
    activateCursor();
    mvwprintw(win, 0, 2, "Salvar Score");
    int l = 1;
    mvwprintw(win, l++, 2, "Nome         :________________");
    mvwprintw(win, l++, 2, "Nascimento   :__/__/____");
    mvwprintw(win, l++, 2, "Nacionalidade:__");
    mvwprintw(win, l++, 2, "Endereço     :__________________________");
    mvwprintw(win, l++, 2, "Email        :__________________________");
    wrefresh(win);
    l = 1;
    Player current;
    int dia = 0, mes = 0, ano = 0;
    mvwscanw(win, l++, 16, "%[^\n]", current.name);
    while (dia < 1 || dia > 31) {
        mvwscanw(win, l, 16, "%d", &dia);
    }
    while (mes < 1 || mes > 12) {
        mvwscanw(win, l, 19, "%d", &mes);
    }
    while (ano < 1900 || ano > 2016) {
        mvwscanw(win, l++, 22, "%d", &ano);
    }
    sprintf(current.birthday, "%02d/%02d/%d", dia, mes, ano);
    mvwscanw(win, l++, 16, "%s", current.nationality);
    mvwscanw(win, l++, 16, "%[^\n]", current.address);
    mvwscanw(win, l++, 16, "%s", current.email);
    savePlayerScoreBoard(&current, *totalScore);
    deactivateCursor();
    closeWindow(win, bh, bw);
} /* saveScoreWindow */

void
menu(int * ch, WINDOW ** boardCellsWindow, unsigned int board[][_BSIZE_], unsigned int * totalScore,
  unsigned int * score, char * filename)
{
    switch (*ch) {
        case KEY_F(1):
            showHelp();
            break;
        case KEY_F(2):
            showScoreboard();
            break;
        case KEY_F(3):
            initGame(boardCellsWindow, board, totalScore, score);
            break;
        case KEY_F(4):
            showSaveGameWindow(board, totalScore, score, filename);
            break;
        case KEY_F(5):
            showLoadGameWindow(board, totalScore, score, filename);
            break;
    }
}

void
initGame(WINDOW ** boardCellsWindow, unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score)
{
    init(board, score, totalScore);
    printScore(totalScore, score);
    printBoard(boardCellsWindow, board);
}

void
printScreen(WINDOW ** boardCellsWindow, unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score,
  char * filename)
{
    printHeader();
    printScore(totalScore, score);
    printBoard(boardCellsWindow, board);
    printFooter(filename);
}

void
noSpaces(char * str)
{
    int i = 0, j = 0;

    while (str[j]) {
        if (isspace(str[j])) {
            while (isspace(str[j])) j++;
        }
        str[i] = str[j];
        i++;
        j++;
    }
    str[i] = 0;
}

void
showSaveGameWindow(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score, char * filename)
{
    WINDOW * win;
    int bh = 3, bw = 64; // box-height; box-width

    win = createWindow(bh, bw, 11, 0);
    if (!strcmp(filename, "lastGame.dat")) { // se vazio
        char msg[] = "Nome do arquivo a salvar:";
        mvwprintw(win, 1, 1, "%s", msg);
        wrefresh(win);
        // filename = (char*)malloc(32*sizeof(char));
        activateCursor();
        mvwgetstr(win, 1, strlen(msg) + 1, filename);
        deactivateCursor();
        noSpaces(filename);
        if (strlen(filename)) {
            if (strstr(filename, ".dat") == NULL) {
                strcat(filename, ".dat");
            }
        } else {
            strcpy(filename, "lastGame.dat");
            closeWindow(win, bh, bw);
            return;
        }
    }
    if (saveGame(board, totalScore, score, filename)) {
        clearWindow(win, bh, bw);
        mvwprintw(win, 1, 2, "Arquivo salvo!");
        wrefresh(win);
        sleep(1);
    }
    closeWindow(win, bh, bw);
}

void
showLoadGameWindow(unsigned int board[][_BSIZE_], unsigned int * totalScore, unsigned int * score, char * filename)
{
    char localFilename[32];
    char msg[62]   = "Nome do save a carregar:";
    char msgQuit[] = "pressione [space] para continuar";
    WINDOW * win;
    int bh = 3, bw = 64; // box-height; box-width

    win = createWindow(bh, bw, 11, 0);
    mvwprintw(win, 1, 1, "%s", msg);
    wrefresh(win);
    activateCursor();
    mvwgetstr(win, 1, strlen(msg) + 1, localFilename);
    deactivateCursor();
    noSpaces(localFilename);
    if (strlen(localFilename)) {
        if (strstr(localFilename, ".dat") == NULL) {
            strcat(localFilename, ".dat");
        }
        strcpy(filename, localFilename);
        if (!loadGame(board, totalScore, score, filename)) {
            clearWindow(win, bh, bw);
            strcpy(msg, "Erro: save não existe. Ao salvar ele será criado");
            mvwprintw(win, 1, 1, "%s", msg);
            mvwprintw(win, 2, (bw - strlen(msgQuit)) - 1, "%s", msgQuit);
            wrefresh(win);
            while (getch() != ' ') ;
        }
    }
    closeWindow(win, bh, bw);
}
