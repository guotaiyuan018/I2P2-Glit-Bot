#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

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

enum class MonsterName
{
    EYEBALL,
    ZAPPER,
    EXPLODER
};

enum class MonsterDirection
{
    LEFT,
    RIGHT
};

enum class MonsterState
{
    ATTACK,
    DEAD,
    DAMAGED,
    MOVE
};

class Monster : public Object
{
public:
    Monster(int, int, int);
    void Update();
    void Damaged(int damage_val)
    {
        hp -= damage_val;
        if (hp > 0)
        {
            state = MonsterState::DAMAGED;
            sprite_pos = 0;
            start_damaged = true;
        }
    }
    void Draw();
    int getHP() { return this->hp; }
    bool getDying() { return start_death; }
    bool getDead() { return is_dead; }

private:
    int MONSTER_WIDTH = 192, MONSTER_HEIGHT = 192;
    int sprite_pos = 1;
    int counter = 0;
    int speed = 0;
    int hp = 10;
    int attack_range = 10;
    bool is_dead = false;
    bool start_death = false;
    bool start_damaged = false;
    MonsterName my_name = MonsterName::EXPLODER;
    MonsterState state = MonsterState::MOVE;
    MonsterDirection direction = MonsterDirection::RIGHT;
    std::map<MonsterName, std::map<MonsterDirection, std::map<MonsterState, std::vector<ALLEGRO_BITMAP *>>>> imgData;
    std::map<MonsterName, std::map<MonsterDirection, std::map<MonsterState, int>>> imgCount;
};

#endif
