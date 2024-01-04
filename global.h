#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define window_width 1200
#define window_height 900
#define grid_width 40
#define grid_height 40

#define field_width 1200
#define field_height 900

#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_down;
extern bool fired;
extern bool shooted;
extern bool game_mute;
extern int hero_x;
extern int hero_y;
extern bool game_mute;


#endif // GLOBAL_H_INCLUDED
