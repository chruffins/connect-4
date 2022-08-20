#include "boardgui.h"

void draw_board() {
    for (int row = 0; row < BOARDROWS; row++) {
        draw_row_circles((row*90)+145);
    }
}

void draw_moves(Board* b) {
    for (int x = 0; x < BOARDROWS; x++) {
        for (int y = 0; y < BOARDCOLUMNS; y++) {
            unsigned char t = get_in_matrix(b->board, x, y);
            if (t) {
                al_draw_filled_circle((y*90)+50, ((BOARDROWS-(1+x))*90)+145, 35, get_plr_color(t));
            }
        }
    }
}

void draw_row_circles(int y) {
    for (int i = 0; i < BOARDCOLUMNS; i++) {
        al_draw_circle((i*90)+50, y, 36, al_map_rgb(255,255,255), 2);
    }
}

void draw_hover_input(Board* b, unsigned char col) {
    al_draw_filled_circle((col*90)+50, 60, 35, get_plr_color(b->plrTurn));
    al_draw_circle((col*90)+50, 60, 36, al_map_rgb(255,255,255), 2);
}

ALLEGRO_COLOR get_plr_color(unsigned char plr) {
    switch (plr)
    {
    case 1:
        return al_map_rgb(255,0,0);
    case 2:
        return al_map_rgb(255,255,0);
    default:
        printf("God has punished you for your transgression.");
        return al_map_rgb(0,255,0);
    }
}

unsigned char get_col_input(float mx) {
    return (int)((mx / BOARDWIDTH) * BOARDCOLUMNS);  
}

void run_connect4board_gui() {
    Board* board = create_board();
    //add_piece(board, 0);

    // gui stuff
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 10.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(BOARDWIDTH, BOARDHEIGHT);

    unsigned char col_input = 0;
    unsigned char new_col_input = 1;
    char game_state;

    //al_register_event_source(queue, al_get_keyboard_event_source());
    al_set_window_title(disp, "Connect 4");
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        if((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;
        else if((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && game_state == 0) {
            col_input = get_col_input(event.mouse.x);
            game_state = advance_turn(board, (int)col_input);
            redraw = true;
        }
        else if((event.type == ALLEGRO_EVENT_MOUSE_AXES) && game_state == 0) {
            new_col_input = get_col_input(event.mouse.x);
            //printf("%d",(int)new_col_input);
            if (new_col_input != col_input) {
                redraw = true;
                col_input = new_col_input;
            }
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_board();
            draw_moves(board);
            draw_hover_input(board, new_col_input);

            switch (game_state)
            {
            case 1:
                printf("Red has won!\n");
                break;
            case 2:
                printf("Yellow has won!\n");
            default:
                break;
            }
            //draw_x(40,40,120,120,al_map_rgb(255,0,0),10);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    printf("The lunatic is on the grass\n");
}