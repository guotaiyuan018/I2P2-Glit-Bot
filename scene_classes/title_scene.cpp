#include "title_scene.h"
#include "../DataCenter.h"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

Title_scene::Title_scene(){
    //create ui interface
    title_interface[START_BUTTON] = {90, 750, 240, 850};
    title_interface[SET_BUTTON] = {241, 750, 465, 850};
    title_interface[CREDIT_BUTTON] = {466, 750, 660, 850};
}

void Title_scene::load_scene(){
    char buffer[50];
    for(int i = 0; i < title_frames; i++){
        sprintf(buffer, "./Scenes/start/breakdown/%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) title_animation.push_back(img);
    }
    for(int i = 0; i < title_ui_num; i++){
        sprintf(buffer, "./Scenes/start/title_menu/%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) title_ui.push_back(img);
    }

}

void Title_scene::draw_background(int counter){
    al_draw_bitmap(title_animation[counter], 0, 0, 0);
}

void Title_scene::draw_ui(){
    al_draw_bitmap(title_ui[cur_menu], 0, 0, 0);
}

//get hovered button
int Title_scene::mouse_act(int x, int y){
    if(x >= title_interface[START_BUTTON][0] && x <= title_interface[START_BUTTON][2]
        && y >= title_interface[START_BUTTON][1] && y <= title_interface[START_BUTTON][3]){
            cur_menu = START_BUTTON;
            return START_BUTTON;
    }
    else if(x >= title_interface[SET_BUTTON][0] && x <= title_interface[SET_BUTTON][2]
        && y >= title_interface[SET_BUTTON][1] && y <= title_interface[SET_BUTTON][3]){
            cur_menu = SET_BUTTON;
            return SET_BUTTON;
    }
    else if(x >= title_interface[CREDIT_BUTTON][0] && x <= title_interface[CREDIT_BUTTON][2]
        && y >= title_interface[CREDIT_BUTTON][1] && y <= title_interface[CREDIT_BUTTON][3]){
            cur_menu = CREDIT_BUTTON;
            return CREDIT_BUTTON;
    }
    else{
        cur_menu = DEFAULT_BUTTON;
        return DEFAULT_BUTTON;
    }
}

Title_scene::~Title_scene(){
    for(int i = 0; i < title_frames; i++)al_destroy_bitmap(title_animation[i]);
    for(int i = 0; i < title_ui_num; i++)al_destroy_bitmap(title_ui[i]);
}
