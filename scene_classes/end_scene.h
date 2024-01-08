#ifndef END_SCENE_H_INCLUDED
#define END_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include "../global.h"
#include <map>
#include <vector>
#include <string>

#define end_ui_num 3

#define NEW_BUTTON 0
#define END_CRE_BUTTON 1
#define EXIT_BUTTON 2
#define NO_HOVERED INT_MAX

using namespace std;

class End_scene{
public:
    End_scene();
    ~End_scene();

    void load_scene();
    void draw_background();
    void draw_ui();
    int mouse_act(int x, int y);
    int update_ui(int button, bool hovered);

private:
    ALLEGRO_BITMAP* win;
    ALLEGRO_BITMAP* loose;
    ALLEGRO_BITMAP* end_ui[end_ui_num][2];
    ALLEGRO_BITMAP* cur_end_ui[end_ui_num];
    int cur_menu = 0;

    map <int, array<int, 4>>end_interface;
};


#endif // END_SCENE_H_INCLUDED
