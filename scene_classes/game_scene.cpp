#include "game_scene.h"

#include <iostream>
#include <map>

using namespace std;

Game_scene::Game_scene(){
    game_interface[PAUSE_BUTTON] = {1080, 50, 1150, 150};
}

void Game_scene::load_scene(){
    char buffer[50];
    for(int i = 0; i < map_num; i++){
        sprintf(buffer, "./Scenes/maps/%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) maps.push_back(img);
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            sprintf(buffer, "./Scenes/battle/controller/%d_%d.png", i, j);
            ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
            if(img) controller[i][j] = img;
        }
        cur_controller[i] = controller[i][0];
    }

    //load hp bars
    for(int i = 0; i <= 10; i++){
        sprintf(buffer, "./Scenes/battle/HP/%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) hp_bar1.push_back(img);

        sprintf(buffer, "./Scenes/battle/boss_stage/hero/%d.png", i);
        img = al_load_bitmap(buffer);
        if(img) hp_bar2.push_back(img);

        sprintf(buffer, "./Scenes/battle/boss_stage/boss/%d.png", i*5);
        img = al_load_bitmap(buffer);
        if(img) boss_hp.push_back(img);
    }


    //load bot info
    for(int i = 0; i < 3; i++){
        sprintf(buffer, "./Scenes/battle/bot_info/%d.png", i);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) bot_info.push_back(img);
    }

    //load bonus stage
    for(int i = 0; i < 20; i++){
        sprintf(buffer, "./Scenes/bonus/bonus_%d.png", i+1);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) bonus.push_back(img);
    }

    pause[0] = al_load_bitmap("./Scenes/battle/pause/0.png");
    pause[1] = al_load_bitmap("./Scenes/battle/pause/1.png");

    text = al_load_bitmap("./Scenes/battle/heal.png");
}

void Game_scene::draw_background(int counter){
    if(cur_stage == 2){
        al_draw_bitmap(bonus[counter], 0, 0, 0);
    }
    else if(cur_stage == 3){
        al_draw_bitmap(maps[2], 0, 0, 0);
    }
    else al_draw_bitmap(maps[cur_stage], 0, 0, 0);
}

void Game_scene::draw_ui(){
    al_draw_bitmap(pause[cur_menu], 0, 0, 0);

    for(int i = 0; i < 4; i++){
        al_draw_bitmap(cur_controller[i], 0, 0, 0);
    }

    al_draw_bitmap(bot_info[DC->get_Hero().front()->getNAME()], 0, 0, 0);

    if(cur_stage == 2)
    {
        if(hero_x <= 750 && hero_x >= 450 && hero_y <= 600 && hero_y >= 300)
        {
            healing = true;
            al_draw_bitmap(text, hero_x - 66, hero_y - 90, 0);
        }
        else healing = false;
    }
    else healing = false;

    if(cur_stage == 3)
    {
        al_draw_bitmap(hp_bar2[DC->get_Hero().front()->getHP()], hero_x - 50, hero_y - 70, 0);

        int tmp;
        if(DC->get_Boss().empty()) tmp = 0;
        else tmp = DC->get_Boss().front()->getHP();

        int b_hp = (tmp + 4) / 5;
        cout << b_hp << endl;
        al_draw_bitmap(boss_hp[b_hp < 0 ? 0 : b_hp], 0, 0, 0);
    }
    else
    {
        al_draw_bitmap(hp_bar1[DC->get_Hero().front()->getHP()], 0, 0, 0);
    }
}

void Game_scene::keyboard_act(){
    if(key_state[ALLEGRO_KEY_W])cur_controller[W_BUTTON] = controller[W_BUTTON][1];
    else cur_controller[W_BUTTON] = controller[W_BUTTON][0];

    if(key_state[ALLEGRO_KEY_A])cur_controller[A_BUTTON] = controller[A_BUTTON][1];
    else cur_controller[A_BUTTON] = controller[A_BUTTON][0];

    if(key_state[ALLEGRO_KEY_S])cur_controller[S_BUTTON] = controller[S_BUTTON][1];
    else cur_controller[S_BUTTON] = controller[S_BUTTON][0];

    if(key_state[ALLEGRO_KEY_D])cur_controller[D_BUTTON] = controller[D_BUTTON][1];
    else cur_controller[D_BUTTON] = controller[D_BUTTON][0];
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
    for(int i = 0; i < bonus_frames; i++)al_destroy_bitmap(bonus[i]);
    for(int i = 0; i < 2; i++)al_destroy_bitmap(pause[i]);
    for(int i = 0; i < 4; i++){
        for(int j = 0;j < 2; j++)al_destroy_bitmap(controller[i][j]);
        al_destroy_bitmap(cur_controller[i]);
    }
    for(int i = 0; i < 10; i++)al_destroy_bitmap(hp_bar1[i]);
    for(int i = 0; i < 3; i++)al_destroy_bitmap(bot_info[i]);
}
