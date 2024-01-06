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
    Monster(int, int);
    void Update();
    void Damaged();
    void Draw();
    int getHP() { return this->hp; }

private:
    int MONSTER_WIDTH = 192, MONSTER_HEIGHT = 192;
    int sprite_pos = 1;
    int counter = 0;
    int speed = 3;
    int hp = 10;
    int attack_range = 10;
    MonsterState state = MonsterState::MOVE;
    MonsterDirection direction = MonsterDirection::RIGHT;
    std::map<MonsterDirection, std::map<MonsterState, std::vector<ALLEGRO_BITMAP *>>> imgData;
    std::map<MonsterDirection, std::map<MonsterState, int>> imgCount;
};

#endif
