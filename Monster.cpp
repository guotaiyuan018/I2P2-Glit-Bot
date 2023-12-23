#include "Monster.h"
#include <iostream>
#include <cmath>

const char direction_name[][100] = {"LEFT_ATTACK", "RIGHT_ATTACK", "LEFT_DEAD", "RIGHT_DEAD", "LEFT_DAMAGED", "RIGHT_DAMAGED", "LEFT_MOVE", "RIGHT_MOVE"};

const int draw_frequency = 10;

Monster::Monster(int x, int y)
{
    this->circle = new Circle(x, y, 100);

    imgCount[MonsterState::LEFT_ATTACK] = 4;
    imgCount[MonsterState::RIGHT_ATTACK] = 4;
    imgCount[MonsterState::LEFT_DEAD] = 6;
    imgCount[MonsterState::RIGHT_DEAD] = 6;
    imgCount[MonsterState::LEFT_DAMAGED] = 2;
    imgCount[MonsterState::RIGHT_DAMAGED] = 2;
    imgCount[MonsterState::LEFT_MOVE] = 2;
    imgCount[MonsterState::RIGHT_MOVE] = 2;

    char buffer[50];
    for (int i = 0; i < sizeof(direction_name) / sizeof(direction_name[0]); i++)
    {
        for (int j = 0; j < imgCount[static_cast<MonsterState>(i)]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./srcs/Monster/MONSTER_%s_%d.png", direction_name[i], j + 1);
            img = al_load_bitmap(buffer);
            if (img)
            {
                imgData[static_cast<MonsterState>(i)].push_back(img);
            }
            else
                std::cout << buffer << std::endl;
        }
    }
}

void Monster::Update()
{
    float dx = hero_x - this->circle->x;
    float dy = hero_y - this->circle->y;
    float lenth = sqrt(dx * dx + dy * dy);
    /*if (lenth > attack_range)
            if (dx > 0)
                direction = MonsterState::RIGHT_MOVE;
            else
                direction = MonsterState::LEFT_MOVE;
        else if (dx > 0)
            direction = MonsterState::RIGHT_ATTACK;
        else
            direction = MonsterState::LEFT_ATTACK;*/

    if (lenth > 0)
    {
        dx /= lenth;
        dy /= lenth;
    }

    this->circle->x += dx * speed;
    this->circle->y += dy * speed;
}

void Monster::Draw()
{
    sprite_pos = (sprite_pos >= imgCount[direction]) ? sprite_pos % imgCount[direction] : sprite_pos;
    al_draw_bitmap(imgData[direction][sprite_pos], this->circle->x, this->circle->y, 0);
}
