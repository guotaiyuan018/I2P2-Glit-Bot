#ifndef GAME_SCENE_H_INCLUDED
#define GAME_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <vector>
#include <map>
#include <string>

#define map_num 2

#define DEFAULT_BUTTON 0
#define PAUSE_BUTTON 1

#define NO_MOVE 0
#define RIGHT 1
#define UP_RIGHT 2
#define UP 3
#define UP_LEFT 4
#define LEFT 5
#define DOWN_LEFT 6
#define DOWN 7
#define DOWN_RIGHT 8

using namespace std;

class Game_scene{
public:
    Game_scene();
    ~Game_scene();

    void load_scene();
    void draw_scene();
    int mouse_act(int x, int y);
    int controller_state = 0;

private:
    vector<ALLEGRO_BITMAP*> maps;
    vector<ALLEGRO_BITMAP*> hp_bar;
    vector<ALLEGRO_BITMAP*> bots;
    vector<ALLEGRO_BITMAP*> controller;
    ALLEGRO_BITMAP* pause[2];

    int cur_menu = 0;
    int cur_bot = 0;

    map <int, array<int, 4>>game_interface;
};


#endif // GAME_SCENE_H_INCLUDED
