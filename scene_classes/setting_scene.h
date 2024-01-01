#ifndef SET_SCENE_H_INCLUDED
#define SET_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include "../global.h"
#include <map>
#include <string>

#define set_ui_num 4

#define RESUME_BUTTON 0
#define RESTART_BUTTON 1
#define EXIT_BUTTON 2
#define AUDIO_BUTTON 3
#define NO_HOVERED INT_MAX

using namespace std;

class Setting_scene{
public:
    Setting_scene();
    ~Setting_scene();

    void load_scene();
    void draw_background();
    void draw_ui();
    int mouse_act(int x, int y);

private:
    ALLEGRO_BITMAP* set_background = NULL;
    ALLEGRO_BITMAP* cur_set_ui[set_ui_num];
    ALLEGRO_BITMAP* set_ui[set_ui_num + 1][2];

    int audio_state = 0;

    map <int, array<int, 5>>set_interface;
};


#endif // SET_SCENE_H_INCLUDED
