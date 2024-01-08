#include "global.h"

bool exit_game = false;
bool reset_game = false;
bool stage_clear = false;

bool key_state[ALLEGRO_KEY_MAX];
bool mouse_down = false;

bool start_atk = false;

bool game_mute = false;

bool loading = false;

bool healing = false;

bool game_won = false;

int hero_x = window_width / 2;
int hero_y = window_height / 2;

int mouse_x, mouse_y;

int cur_scene = 0;
int prev_scene = 0;

int cur_stage = 0;

ALLEGRO_BITMAP* load_page[4];
