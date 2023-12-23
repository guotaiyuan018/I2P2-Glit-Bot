#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <map>
#include "Object.h"
#include "Circle.h"
#include "global.h"

enum class MonsterState
{
    LEFT_ATTACK,
    RIGHT_ATTACK,
    LEFT_DEAD,
    RIGHT_DEAD,
    LEFT_DAMAGED,
    RIGHT_DAMAGED,
    LEFT_MOVE,
    RIGHT_MOVE
};

class Monster : public Object
{
public:
    Monster(int, int);
    void Update();
    void Draw();

private:
    int x, y;
    int sprite_pos = 1;
    int speed = 3;
    int hp = 10;
    int attack_range = 10;
    MonsterState direction = MonsterState::RIGHT_MOVE;
    std::map<MonsterState, std::vector<ALLEGRO_BITMAP *>> imgData;
    std::map<MonsterState, int> imgCount;
};

#endif