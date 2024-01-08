#include "end_scene.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

End_scene::End_scene()
{
    end_interface[NEW_BUTTON] = {250, 590, 400, 650};
    end_interface[END_CRE_BUTTON] = {530, 590, 670, 650};
    end_interface[EXIT_BUTTON] = {800, 590, 900, 650};
}

void End_scene::load_scene()
{
    char buffer[50];

    win = al_load_bitmap("./Scenes/end/background.png");
    for(int i = 0; i < end_ui_num; i++){
        for(int j = 0; j < 2; j++){
            sprintf(buffer, "./Scenes/end/%d_%d.png", i, j);
            ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
            if(img) end_ui[i][j] = img;
        }
        cur_end_ui[i] = end_ui[i][0];
    }
}

void End_scene::draw_background()
{
    al_draw_bitmap(win, 0, 0, 0);

}

void End_scene::draw_ui()
{
    for(int i = 0; i < end_ui_num; i++){
        al_draw_bitmap(cur_end_ui[i], 0, 0, 0);
    }
}

int End_scene::mouse_act(int x, int y)
{
    if(x >= end_interface[NEW_BUTTON][0] && x <= end_interface[NEW_BUTTON][2]
       && y >= end_interface[NEW_BUTTON][1] && y <= end_interface[NEW_BUTTON][3]){
            cur_end_ui[NEW_BUTTON] = end_ui[NEW_BUTTON][1];
            return NEW_BUTTON;
       }
    else{
        cur_end_ui[NEW_BUTTON] = end_ui[NEW_BUTTON][0];
    }

    if(x >= end_interface[END_CRE_BUTTON][0] && x <= end_interface[END_CRE_BUTTON][2]
       && y >= end_interface[END_CRE_BUTTON][1] && y <= end_interface[END_CRE_BUTTON][3]){
            cur_end_ui[END_CRE_BUTTON] = end_ui[END_CRE_BUTTON][1];
            return END_CRE_BUTTON;
       }
    else{
        cur_end_ui[END_CRE_BUTTON] = end_ui[END_CRE_BUTTON][0];
    }

    if(x >= end_interface[EXIT_BUTTON][0] && x <= end_interface[EXIT_BUTTON][2]
       && y >= end_interface[EXIT_BUTTON][1] && y <= end_interface[EXIT_BUTTON][3]){
            cur_end_ui[EXIT_BUTTON] = end_ui[EXIT_BUTTON][1];
            return EXIT_BUTTON;
       }
    else{
        cur_end_ui[EXIT_BUTTON] = end_ui[EXIT_BUTTON][0];
    }

    return NO_HOVERED;
}

End_scene::~End_scene()
{
    al_destroy_bitmap(win);

    for(int i = 0; i < end_ui_num; i++){
        for(int j = 0; j < 2; j++)
            al_destroy_bitmap(end_ui[i][j]);
    }

    for(int i = 0; i < end_ui_num; i++){
        al_destroy_bitmap(cur_end_ui[i]);
    }
}
