#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "scene_classes/title_scene.h"
#include "scene_classes/game_scene.h"
#include "scene_classes/setting_scene.h"
// #include "scene_classes/end_scene.h"

#include <vector>
using namespace std;

enum
{
    TITLE_SCENE = 0,
    BATTLE_SCENE = 1,
    SET_SCENE = 2,
    CREDIT_SCENE = 3
};

class Scene_manager
{
public:
    Scene_manager();
    ~Scene_manager();

    void load_scenes();
    void draw_background(int anime_counter);
    void draw_ui();
    void mouse_in(int x, int y);
    void key_in();
    void change_scene();
    int get_current() { return current_scene; }

private:
    int current_scene = 0;
    int prev_scene = 0;
    int mouse_on = 0;

    Title_scene *title_scene = NULL;
    Game_scene *game_scene = NULL;
    Setting_scene *setting_scene = NULL;
    // End_scene *end_scene = NULL;

    ALLEGRO_BITMAP *credit_scene = NULL;
    ALLEGRO_BITMAP *crosshair = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *title_bgm = NULL;
    ALLEGRO_SAMPLE_INSTANCE *game_bgm = NULL;
};

#endif // SCENE_H_INCLUDED
