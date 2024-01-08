#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <list>
#include <time.h>
#include "global.h"
#include "DataCenter.h"
#include "scene_manager.h"
#include "Bullet.h"
#include "Monster.h"
#include "Zone.h"
#include "Portal.h"
#include "Boss.h"

#define STAGE_NUM 3

#define GAME_INIT -1
#define GAME_LOADING 0
#define GAME_BEGIN 1
#define GAME_CONTINUE 2
#define GAME_WIN 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_MAP 6
#define GAME_EXIT 7

#define window_width 1200
#define window_height 900

using namespace std;

const float FPS = 60;

class game_window
{
public:
    game_window();

    void game_init();
    void game_reset();
    void game_begin(); // draw init scene
    void game_play();

    void set_enemy(int);

    int game_run();
    int game_update();
    int process_event(); // now the only event is keydown to change scene

    void draw_scene(); // flip display here

    void game_destroy();
    void show_err_msg(int msg);

    Bullet *create_bullet(int, int, int);
    Monster *create_monster(int, int, int);
    Boss *create_boss();
    Zone *create_zone(int, int);

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *crosshair_cursor;
    ALLEGRO_BITMAP *arrow_cursor;
    ALLEGRO_MOUSE_CURSOR *crosshair;
    ALLEGRO_MOUSE_CURSOR *cursor;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *glitch_timer = NULL;
    ALLEGRO_TIMER *boss_timer = NULL;
    ALLEGRO_TIMER *monster_pro = NULL;
    ALLEGRO_TIMER *monster_timer = NULL;

    Scene_manager *scene_manager = NULL;

    int Monster_Pro_Count = 0;
    int Bullet_Pro_Count = 0;
    int counter = 0;

    vector<Bullet *> &bulletSet = DC->get_Bullet();
    vector<Monster *> &monsterSet = DC->get_Monster();
    list<Hero *> &heroSet = DC->get_Hero();
    list<Boss *> &bossSet = DC->get_Boss();
    list<Zone *> &zoneSet = DC->get_Zone();

    Portal *portal = NULL;

    bool frame_update = false;
    bool enter_portal = false;
    bool load_next = false;
};

#endif // MAINWINDOW_H_INCLUDED
