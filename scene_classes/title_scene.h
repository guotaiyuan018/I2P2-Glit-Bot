#ifndef TITLE_SCENE_H_INCLUDED
#define TITLE_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <map>

#define title_frames 184
#define title_ui_num 4

#define DEFAULT_BUTTON 0
#define START_BUTTON 1
#define SET_BUTTON 2
#define CREDIT_BUTTON 3

using namespace std;

class Title_scene{
public:
    Title_scene();
    ~Title_scene();

    void load_scene();
    void draw_scene(int counter);
    int mouse_act(int x, int y);

private:
    vector<ALLEGRO_BITMAP*> title_ui;
    vector<ALLEGRO_BITMAP*> title_animation;
    int cur_menu = 0;

    map <int, array<int, 4>>title_interface;//map<button name, button position>
};


#endif // TITLE_SCENE_H_INCLUDED
