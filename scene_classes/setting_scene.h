#ifndef SET_SCENE_H_INCLUDED
#define SET_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include "../global.h"
#include <map>
#include <string>

#define set_ui_num 5

#define DEFAULT_BUTTON 0
#define RESUME_BUTTON 1
#define RESTART_BUTTON 2
#define EXIT_BUTTON 3
#define AUDIO_BUTTON 4

using namespace std;

class Setting_scene{
public:
    Setting_scene();
    ~Setting_scene();

    void load_scene();
    void draw_scene();
    int mouse_act(int x, int y);

private:
    ALLEGRO_BITMAP* set_background = NULL;
    ALLEGRO_BITMAP* audio_state[2][2];//[button index][state]
    ALLEGRO_BITMAP* set_ui[set_ui_num][2];//[button index][state]

    int cur_menu = 0;

    map <int, array<int, 5>>set_interface;
};


#endif // SET_SCENE_H_INCLUDED
