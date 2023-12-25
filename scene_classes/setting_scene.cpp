#include "setting_scene.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

//create ui interface
Setting_scene::Setting_scene(){
    game_mute = false;
    set_interface[RESUME_BUTTON] = {520, 340, 680, 370};
    set_interface[RESTART_BUTTON] = {490, 460, 710, 490};
    set_interface[EXIT_BUTTON] = {540, 690, 650, 740};
    set_interface[AUDIO_BUTTON] = {450, 550, 750, 620};
}

void Setting_scene::load_scene(){
    //cout << "load set scene\n";
    char buffer[50];
    for(int i = 0; i < set_ui_num - 2; i++){
        for(int j = 0; j < 2; j++){
            sprintf(buffer, "./Scenes/settings/%d_%d.png", i, j);
            ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
            if(img) set_ui[i][j] = img;
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            sprintf(buffer, "./Scenes/settings/%d_%d.png", i + 3, j);
            ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
            if(img) audio_state[i][j] = img;
        }
    }
    set_background = al_load_bitmap("./Scenes/settings/background.png");
}

void Setting_scene::draw_scene(){
    al_draw_bitmap(set_background, 0, 0, 0);
    if(cur_menu == DEFAULT_BUTTON){
        for(int i = 0; i < set_ui_num - 2; i++){
            al_draw_bitmap(set_ui[i][0], 0, 0, 0);
        }
        al_draw_bitmap(audio_state[!game_mute][0], 0, 0, 0);
    }
    else {
        for(int i = 0; i < set_ui_num - 2; i++){
            if(i+1 == cur_menu)al_draw_bitmap(set_ui[i][1], 0, 0, 0);
            else al_draw_bitmap(set_ui[i][0], 0, 0, 0);
        }
        al_draw_bitmap(audio_state[!game_mute][cur_menu == AUDIO_BUTTON], 0, 0, 0);
    }
}

//get hovered button
int Setting_scene::mouse_act(int x, int y){
    if(x >= set_interface[RESUME_BUTTON][0] && x <= set_interface[RESUME_BUTTON][2]
       && y >= set_interface[RESUME_BUTTON][1] && y <= set_interface[RESUME_BUTTON][3]){
        cur_menu = RESUME_BUTTON;
        return RESUME_BUTTON;
    }
    else if(x >= set_interface[RESTART_BUTTON][0] && x <= set_interface[RESTART_BUTTON][2]
            &&y >= set_interface[RESTART_BUTTON][1] && y <= set_interface[RESTART_BUTTON][3]){
        cur_menu = RESTART_BUTTON;
        return RESTART_BUTTON;
    }
    else if(x >= set_interface[EXIT_BUTTON][0] && x <= set_interface[EXIT_BUTTON][2]
            && y >= set_interface[EXIT_BUTTON][1] && y <= set_interface[EXIT_BUTTON][3]){
        cur_menu = EXIT_BUTTON;
        return EXIT_BUTTON;
    }
    else if(x >= set_interface[AUDIO_BUTTON][0] && x <= set_interface[AUDIO_BUTTON][2]
            && y >= set_interface[AUDIO_BUTTON][1] && y <= set_interface[AUDIO_BUTTON][3]){
        cur_menu = AUDIO_BUTTON;
        return AUDIO_BUTTON;
    }
    else{
        cur_menu = DEFAULT_BUTTON;
        return DEFAULT_BUTTON;
    }
}

Setting_scene::~Setting_scene(){
    for(int i = 0; i < set_ui_num; i++){
        for(int j = 0; j < 2; j++){
            al_destroy_bitmap(set_ui[i][j]);
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            al_destroy_bitmap(audio_state[i][j]);
        }
    }
    al_destroy_bitmap(set_background);
}
