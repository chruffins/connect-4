#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "boardgui.h"
#include "stdio.h"

int main() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    run_connect4board_gui();
    return 0;
}