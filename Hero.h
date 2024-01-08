#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include <iostream>
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
    GLITCH,
    DAMAGED
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
    void Attack();
    void Glitch(int);
    void Damaged(int damage)
    {
        if (!start_damaged && !start_glitch)
        {
            std::cout << hero_hp << std::endl;
            hero_hp -= damage;
            sprite_pos = 0;
            state = HeroState::DAMAGED;
        }
        start_damaged = true;
    }

    void heal(int counter)
    {
        if (!(counter % 150))
        {
            if (hero_hp < 10)
                hero_hp++;
        }
    }

    int getHP() { return hero_hp; }
    int getNAME() { return static_cast<int>(my_name); }

private:
    int HERO_WIDTH = 448, HERO_HEIGHT = 448;
    int x, y;
    int counter = 0;
    int sprite_pos = 1;
    int speed = 2;
    int hero_hp = 10;
    bool start_glitch = false;
    bool start_damaged = false;
    HeroDirection direction = HeroDirection::RIGHT;
    HeroState state = HeroState::IDLE;
    HeroName my_name = HeroName::BEAM;
    std::map<HeroName, std::map<HeroDirection, std::map<HeroState, std::vector<ALLEGRO_BITMAP *>>>> imgData;
    // ALLEGRO_BITMAP *imgData;
    std::map<HeroDirection, std::map<HeroState, int>> imgCount;
};

#endif
