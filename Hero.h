#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <map>
#include "Object.h"
#include "Circle.h"
#include "global.h"

enum class HeroState
{
    RIGHT_MOVE,
    LEFT_MOVE,
    RIGHT_IDLE,
    LEFT_IDLE
};

class Hero : public Object
{
public:
    Hero();
    void Update();
    void Draw();
    std::pair<int, int> Pos();

private:
    int x, y;
    int counter;
    int sprite_pos = 1;
    int speed = 5;
    HeroState direction = HeroState::RIGHT_MOVE;
    std::map<HeroState, std::vector<ALLEGRO_BITMAP *>> imgData;
    // ALLEGRO_BITMAP *imgData;
    std::map<HeroState, int> imgCount;
};

#endif