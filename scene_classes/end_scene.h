#ifndef END_SCENE_H_INCLUDED
#define END_SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <map>
#include <vector>
#include <string>

#define DEFAULT_BUTTON 0
#define HOME_BUTTON 1
#define EXIT_BUTTON 2

class End_scene{
public:
    End_scene();
    ~End_scene();

    void load_scene();
    void draw_scene();
    void mouse_act(int x, int y);
    int update_ui(int button, bool hovered);

private:
    ALLEGRO_BITMAP* win;
    ALLEGRO_BITMAP* loose;
    vector<ALLEGRO_BITMAP*> end_ui;
    int cur_menu = 0;

    map <int, array<int, 3>>end_interface;
};


#endif // END_SCENE_H_INCLUDED
