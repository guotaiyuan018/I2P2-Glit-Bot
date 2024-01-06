#ifndef GAME_SCENE_H_INCLUDED
#define GAME_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include "../global.h"
#include "../Hero.h"
#include "../DataCenter.h"
#include <vector>
#include <map>
#include <string>

#define bonus_frames 20
#define map_num 2

#define DEFAULT_BUTTON 0
#define PAUSE_BUTTON 1

#define W_BUTTON 0
#define A_BUTTON 1
#define S_BUTTON 2
#define D_BUTTON 3

using namespace std;

class Game_scene{
public:
    Game_scene();
    ~Game_scene();

    void load_scene();
    void draw_background(int counter);
    void draw_ui();
    int mouse_act(int x, int y);
    void keyboard_act();

private:
    vector<ALLEGRO_BITMAP*> maps;
    vector<ALLEGRO_BITMAP*> bonus;
    vector<ALLEGRO_BITMAP*> hp_bar;// hp = 10
    vector<ALLEGRO_BITMAP*> bot_info;// 3 bots
    ALLEGRO_BITMAP* cur_controller[4];
    ALLEGRO_BITMAP* controller[4][2];
    ALLEGRO_BITMAP* pause[2];

    int cur_menu = 0;
    int cur_bot = 0;

    map <int, array<int, 4>>game_interface;
};


#endif // GAME_SCENE_H_INCLUDED
