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
    LEFT_MOVE,
    RIGHT_MOVE,
    LEFT_IDLE,
    RIGHT_IDLE,
    LEFT_ATTACK,
    RIGHT_ATTACK
};

enum class HeroName
{
    BULLET,
    BLADE
};

class Hero : public Object
{
public:
    Hero();
    void Update();
    void Draw();

private:
    int hero_count = 2;
    int HERO_WIDTH = 256, HERO_HEIGHT = 256;
    int x, y;
    int counter;
    int sprite_pos = 1;
    int speed = 5;
    HeroState direction = HeroState::RIGHT_IDLE;
    HeroName my_name = HeroName::BLADE;
    std::map<HeroName, std::map<HeroState, std::vector<ALLEGRO_BITMAP *>>> imgData;
    // ALLEGRO_BITMAP *imgData;
    std::map<HeroState, int> imgCount;
};

#endif