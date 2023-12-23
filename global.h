#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 1200
#define window_height 900
#define field_width 1200
#define field_height 900

#define Num_TowerType 5
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int TowerRadius[];
extern char TowerClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_down;
extern bool fired;
extern bool shooted;
extern int hero_x;
extern int hero_y;

enum
{
    ARCANE = 0,
    ARCHER,
    CANON,
    POISON,
    STORM
};
enum
{
    WOLF = 0,
    WOLFKNIGHT,
    DEMONNIJIA,
    CAVEMAN
};

#endif // GLOBAL_H_INCLUDED
