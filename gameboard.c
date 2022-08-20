#include "gameboard.h"

Board* create_board() {
    Board* b = (Board*)malloc(sizeof(Board));
    b->plrTurn = 1;
    b->turns = 0;
    b->board = new_matrix(7,6);

    return b;
}

void destroy_board(Board* b) {
    dlt_matrix(b->board);
    free(b);
}

char can_add_piece(Board* b, int col) {
    for (char i = 0; i < 6; i++) {
        if (get_in_matrix(b->board, i, col) == 0) {
            return i;
        }
    }
    return -1;
}

char add_piece(Board* b, int col) {
    char row = can_add_piece(b, col);

    if (row > -1) {
        int result = mod_matrix(b->board, row, col, b->plrTurn);
        b->plrTurn = 3 - b->plrTurn;
        b->turns += 1;

        return result;
    }
    return 0;
}

char advance_turn(Board* b, int col) {
    char peed = add_piece(b, col);
    if (peed) {
        unsigned char won = check_victory(b);
        switch (won)
        {
        case 0:
            return 0;
        case 255:
            return -1;
        default:
            return (char)won;
        }
    }
    return 0;
}

unsigned char check_victory(Board* b) {
    Matrix m = *(b->board);
    // row check
    for (int y = 0; y < m.y; y++) {
        for (int x = 0; x < m.x - 3; x++) {
            unsigned char plr = get_in_matrix(&m, x, y);
            if (plr && plr == get_in_matrix(&m, x+1, y) && plr == get_in_matrix(&m, x+2, y) && plr == get_in_matrix(&m, x+3, y)) {
                return plr;
            }
        }
    }

    // column check
    for (int x = 0; x < m.x; x++) {
        for (int y = 0; y < m.y - 3; y++) {
            unsigned char plr = get_in_matrix(&m, x, y);
            if (plr && plr == get_in_matrix(&m, x, y+1) && plr == get_in_matrix(&m, x, y+2) && plr == get_in_matrix(&m, x, y+3)) {
                return plr;
            }
        }
    }

    // ascending diagonal check
    for (int x = 3; x < m.x; x++) {
        for (int y = 0; y < m.y - 3; y++) {
            unsigned char plr = get_in_matrix(&m, x, y);
            if (plr && plr == get_in_matrix(&m, x-1, y+1) && plr == get_in_matrix(&m, x-2, y+2) && plr == get_in_matrix(&m, x-3, y+3)) {
                return plr;
            }
        }
    }

    // descending diagonal check
    for (int x = 3; x < m.x; x++) {
        for (int y = 3; y < m.y; y++) {
            unsigned char plr = get_in_matrix(&m, x, y);
            if (plr && plr == get_in_matrix(&m, x-1, y-1) && plr == get_in_matrix(&m, x-2, y-2) && plr == get_in_matrix(&m, x-3, y-3)) {
                return plr;
            }
        }
    }

    if (b->turns >= 42) {
        return 255;
    }

    return 0;
}