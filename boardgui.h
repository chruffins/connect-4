#ifndef BOARDGUI_H
#define BOARDGUI_H

#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<stdio.h>
#include "gameboard.h"

#define BOARDWIDTH 640
#define BOARDHEIGHT 640

void draw_board();
void draw_moves(Board*);
void draw_row_circles(int);
void draw_hover_input(Board*, unsigned char);

ALLEGRO_COLOR get_plr_color(unsigned char);
unsigned char get_col_input(float mx);
void run_connect4board_gui();

#endif