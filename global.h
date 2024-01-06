#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define window_width 1200
#define window_height 900
#define grid_width 40
#define grid_height 40

#define field_width 1200
#define field_height 900

extern bool exit_game;
extern bool reset_game;
extern bool stage_clear;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_down;
extern bool start_atk;
extern bool game_mute;
extern bool healing;
extern int hero_x;
extern int hero_y;
extern int cur_scene;
extern int prev_scene;
extern int cur_stage;
extern int mouse_x, mouse_y;

#endif // GLOBAL_H_INCLUDED
