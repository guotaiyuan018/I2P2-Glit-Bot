#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <map>
#include "Object.h"
#include "Circle.h"
#include "global.h"

enum class BossDirection
{
    LEFT,
    RIGHT
};

enum class BossState
{
    ATTACK,
    DEAD,
    DAMAGED,
    MOVE,
    WAKE
};

class Boss : public Object
{
public:
    Boss(int, int);
    void Update();
    void Damaged(int damage_val)
    {
        hp -= damage_val;
        if (hp > 0)
        {
            state = BossState::DAMAGED;
            sprite_pos = 0;
            start_damaged = true;
        }
    }
    void Draw();
    int getHP() { return this->hp; }
    bool getDying() { return start_death; }
    bool getDead() { return is_dead; }

private:
    int Boss_WIDTH = 192, Boss_HEIGHT = 192;
    int sprite_pos = 1;
    int counter = 0;
    int speed = 0;
    int hp = 10;
    int attack_range = 10;
    bool is_dead = false;
    bool start_death = false;
    bool start_damaged = false;
    BossState state = BossState::MOVE;
    BossDirection direction = BossDirection::RIGHT;
    std::map<BossState, std::vector<ALLEGRO_BITMAP *>> imgData;
    std::map<BossState, int> imgCount;
};

#endif
