#include "setting_scene.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

//create ui interface
Setting_scene::Setting_scene(){
    game_mute = false;
    set_interface[RESUME_BUTTON] = {520, 260, 660, 310};
    set_interface[RESTART_BUTTON] = {490, 380, 700, 430};
    set_interface[AUDIO_BUTTON] = {490, 510, 710, 550};
    set_interface[EXIT_BUTTON] = {550, 630, 650, 730};
}

void Setting_scene::load_scene(){
    //cout << "load set scene\n";
    char buffer[50];
    for(int i = 0; i < set_ui_num + 1; i++){
        for(int j = 0; j < 2; j++){
            sprintf(buffer, "./Scenes/settings/%d_%d.png", i, j);
            ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
            if(img) set_ui[i][j] = img;
        }
        if(i < 4)cur_set_ui[i] = set_ui[i][0];
    }

    for(int i = 0; i < 2; i++){
        sprintf(buffer, "./Scenes/settings/background%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) set_background[i] = img;
    }
}

void Setting_scene::draw_background(){
    int index = (prev_scene == 0 ? 0 : 1); // prev_scene == TITLE_SCENE ?
    al_draw_bitmap(set_background[index], 0, 0, 0);
}

void Setting_scene::draw_ui(){
    cur_set_ui[AUDIO_BUTTON] = set_ui[AUDIO_BUTTON + (game_mute ? 1 : 0)][audio_state];
    for(int i = 0; i < set_ui_num; i++){
        al_draw_bitmap(cur_set_ui[i], 0, 0, 0);
    }
}

//get hovered button
int Setting_scene::mouse_act(int x, int y){
    if(x >= set_interface[RESUME_BUTTON][0] && x <= set_interface[RESUME_BUTTON][2]
       && y >= set_interface[RESUME_BUTTON][1] && y <= set_interface[RESUME_BUTTON][3]){
        cur_set_ui[RESUME_BUTTON] = set_ui[RESUME_BUTTON][1];
        return RESUME_BUTTON;
    }
    else{
        cur_set_ui[RESUME_BUTTON] = set_ui[RESUME_BUTTON][0];
    }

    if(x >= set_interface[RESTART_BUTTON][0] && x <= set_interface[RESTART_BUTTON][2]
            &&y >= set_interface[RESTART_BUTTON][1] && y <= set_interface[RESTART_BUTTON][3]){
        cur_set_ui[RESTART_BUTTON] = set_ui[RESTART_BUTTON][1];
        return RESTART_BUTTON;
    }
    else{
        cur_set_ui[RESTART_BUTTON] = set_ui[RESTART_BUTTON][0];
    }

    if(x >= set_interface[EXIT_BUTTON][0] && x <= set_interface[EXIT_BUTTON][2]
            && y >= set_interface[EXIT_BUTTON][1] && y <= set_interface[EXIT_BUTTON][3]){
        cur_set_ui[EXIT_BUTTON] = set_ui[EXIT_BUTTON][1];
        return EXIT_BUTTON;
    }
    else{
        cur_set_ui[EXIT_BUTTON] = set_ui[EXIT_BUTTON][0];
    }

    if(x >= set_interface[AUDIO_BUTTON][0] && x <= set_interface[AUDIO_BUTTON][2]
            && y >= set_interface[AUDIO_BUTTON][1] && y <= set_interface[AUDIO_BUTTON][3]){
        audio_state = 1;
        return AUDIO_BUTTON;
    }
    else{
        audio_state = 0;
    }
    return NO_HOVERED;
}

Setting_scene::~Setting_scene(){
    for(int i = 0; i < set_ui_num + 1; i++){
        for(int j = 0; j < 2; j++){
            al_destroy_bitmap(set_ui[i][j]);
        }
        if(i < 4) al_destroy_bitmap(cur_set_ui[i]);
    }
    for(int i = 0; i < 2; i++){
        al_destroy_bitmap(set_background[i]);
    }
}
