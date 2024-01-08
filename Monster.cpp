#include "Monster.h"
#include <iostream>
#include <cmath>

const char state_name[][100] = {"ATTACK", "DEAD", "DAMAGED", "MOVE"};
const char dir_name[][100] = {"LEFT", "RIGHT"};
const char mon_name[][100] = {"EYEBALL", "ZAPPER", "EXPLODER"};

const int draw_frequency = 10;

Monster::Monster(int x, int y, int name)
{
    this->circle = new Circle(x, y, 60);

    my_name = static_cast<MonsterName>(name);

    imgCount[MonsterName::ZAPPER][MonsterState::ATTACK] = 10;
    imgCount[MonsterName::ZAPPER][MonsterState::DEAD] = 16;
    imgCount[MonsterName::ZAPPER][MonsterState::DAMAGED] = 6;
    imgCount[MonsterName::ZAPPER][MonsterState::MOVE] = 6;

    imgCount[MonsterName::EYEBALL][MonsterState::ATTACK] = 11;
    imgCount[MonsterName::EYEBALL][MonsterState::DEAD] = 12;
    imgCount[MonsterName::EYEBALL][MonsterState::DAMAGED] = 6;
    imgCount[MonsterName::EYEBALL][MonsterState::MOVE] = 8;

    imgCount[MonsterName::EXPLODER][MonsterState::ATTACK] = 0;
    imgCount[MonsterName::EXPLODER][MonsterState::DEAD] = 16;
    imgCount[MonsterName::EXPLODER][MonsterState::DAMAGED] = 6;
    imgCount[MonsterName::EXPLODER][MonsterState::MOVE] = 6;

    char buffer[50];

    for (int i = 0; i < sizeof(state_name) / sizeof(state_name[0]); i++)
    {

        for (int j = 0; j < imgCount[my_name][static_cast<MonsterState>(i)]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./Monster/%s/MONSTER_RIGHT_%s_%d.png", mon_name[static_cast<int>(my_name)], state_name[i], j + 1);
            img = al_load_bitmap(buffer);
            if (img)
            {
                imgData[my_name][static_cast<MonsterState>(i)].push_back(img);
            }
            else
                std::cout << buffer << std::endl;
        }
    }
}

void Monster::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[my_name][state];

    float dx = hero_x - this->circle->x;
    float dy = hero_y - this->circle->y;
    float lenth = sqrt(dx * dx + dy * dy);

    if (!start_death)
    {
        if (dx > 0)
            direction = MonsterDirection::RIGHT;
        else
            direction = MonsterDirection::LEFT;
    }

    if (lenth > 0)
    {
        dx /= lenth;
        dy /= lenth;
    }

    this->circle->x += dx * speed;
    this->circle->y += dy * speed;

    if (hp < 0)
    {
        if (!start_death)
            sprite_pos = 0;
        start_death = true;
        state = MonsterState::DEAD;
        speed = 0;
    }
    else if (!start_damaged)
    {
        if (lenth < 300)
        {
            if (my_name != MonsterName::EXPLODER)
                state = MonsterState::ATTACK;
            if (my_name == MonsterName::EYEBALL)
                speed = 4;
        }

        else
        {
            state = MonsterState::MOVE;
            speed = 2;
        }
    }
}
void Monster::Draw()
{
    if (sprite_pos == imgCount[my_name][state] - 1 && state == MonsterState::DEAD)
        is_dead = true;
    if (sprite_pos == imgCount[my_name][state] - 1 && state == MonsterState::DAMAGED)
        start_damaged = false;

    sprite_pos = (sprite_pos >= imgCount[my_name][state]) ? sprite_pos % imgCount[my_name][state] : sprite_pos;
    bool flip_not = (direction == MonsterDirection::RIGHT) ? false : true;
    al_draw_bitmap(imgData[my_name][state][sprite_pos], this->circle->x - MONSTER_WIDTH / 2, this->circle->y - MONSTER_HEIGHT / 2, flip_not);
}
