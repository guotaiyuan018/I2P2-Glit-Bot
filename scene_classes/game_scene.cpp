#include "game_scene.h"

#include <iostream>
#include <map>

using namespace std;

Game_scene::Game_scene(){
    game_interface[PAUSE_BUTTON] = {1075, 20, 1145, 75};
}

void Game_scene::load_scene(){
    char buffer[50];
    for(int i = 0; i < map_num; i++){
        sprintf(buffer, "./Scenes/maps/%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) maps.push_back(img);
    }

    pause[0] = al_load_bitmap("./Scenes/battle/pause/0.png");
    pause[1] = al_load_bitmap("./Scenes/battle/pause/1.png");
}

void Game_scene::draw_scene(){
    al_draw_bitmap(maps[0], 0, 0, 0);
    al_draw_bitmap(pause[cur_menu], 0, 0, 0);
}

int Game_scene::mouse_act(int x, int y){
    if(x >= game_interface[PAUSE_BUTTON][0] && x <= game_interface[PAUSE_BUTTON][2]
        && y >= game_interface[PAUSE_BUTTON][1] && y <= game_interface[PAUSE_BUTTON][3]){
            cur_menu = 1;
            return PAUSE_BUTTON;
       }
    else{
        cur_menu = 0;
        return DEFAULT_BUTTON;
    }
}

Game_scene::~Game_scene(){
    for(int i = 0; i < map_num; i++)al_destroy_bitmap(maps[i]);
    for(int i = 0; i < 2; i++)al_destroy_bitmap(pause[i]);
}
