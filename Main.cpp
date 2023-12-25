#include "game_window.h"

int main(int argc, char *argv[]){
    game_window *GlitBot = new game_window();

    GlitBot->game_play();

    delete GlitBot;
    return 0;
}
