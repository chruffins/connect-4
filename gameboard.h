#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#define BOARDROWS 6
#define BOARDCOLUMNS 7

#include<stdlib.h>
#include"matrix.h"

struct ConnectBoard {
    unsigned char plrTurn;
    unsigned char turns;
    Matrix* board;
} typedef Board;

Board* create_board();
void destroy_board(Board*);
char can_add_piece(Board*, int);
char add_piece(Board*, int);
char advance_turn(Board*, int);
unsigned char check_victory(Board*);

#endif