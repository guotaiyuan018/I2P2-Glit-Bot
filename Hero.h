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

enum class HeroDirection
{
    LEFT,
    RIGHT
};

enum class HeroState
{
    MOVE,
    IDLE,
    ATTACK,
    GLITCH
};

enum class HeroName
{
    BULLET,
    BLADE,
    BEAM
};

class Hero : public Object
{
public:
    Hero();
    void Update();
    void Draw();
    void Glitch(int);
    void Damaged(int damage) { hero_hp -= damage; }

private:
    int HERO_WIDTH = 448, HERO_HEIGHT = 448;
    int x, y;
    int counter = 0;
    int sprite_pos = 1;
    int speed = 5;
    int hero_hp = 10;
    HeroDirection direction = HeroDirection::RIGHT;
    HeroState state = HeroState::IDLE;
    HeroName my_name = HeroName::BEAM;
    std::map<HeroName, std::map<HeroDirection, std::map<HeroState, std::vector<ALLEGRO_BITMAP *>>>> imgData;
    // ALLEGRO_BITMAP *imgData;
    std::map<HeroDirection, std::map<HeroState, int>> imgCount;
};

#endif
