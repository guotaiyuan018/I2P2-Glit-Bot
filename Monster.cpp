#include "Monster.h"
#include <iostream>
#include <cmath>

const char state_name[][100] = {"ATTACK", "DEAD", "DAMAGED", "MOVE"};
const char dir_name[][100] = {"LEFT", "RIGHT"};

const int draw_frequency = 10;

Monster::Monster(int x, int y)
{
    this->circle = new Circle(x - MONSTER_WIDTH / 2, y - MONSTER_HEIGHT / 2, 90);

    imgCount[MonsterDirection::LEFT][MonsterState::ATTACK] = 4;
    imgCount[MonsterDirection::LEFT][MonsterState::DEAD] = 6;
    imgCount[MonsterDirection::LEFT][MonsterState::DAMAGED] = 2;
    imgCount[MonsterDirection::LEFT][MonsterState::MOVE] = 2;
    imgCount[MonsterDirection::RIGHT][MonsterState::ATTACK] = 4;
    imgCount[MonsterDirection::RIGHT][MonsterState::DEAD] = 6;
    imgCount[MonsterDirection::RIGHT][MonsterState::DAMAGED] = 2;
    imgCount[MonsterDirection::RIGHT][MonsterState::MOVE] = 2;

    char buffer[50];
    for (int i = 0; i < sizeof(state_name) / sizeof(state_name[0]); i++)
    {
        for (int k = 0; k < 2; k++)
        {
            for (int j = 0; j < imgCount[static_cast<MonsterDirection>(k)][static_cast<MonsterState>(i)]; j++)
            {
                ALLEGRO_BITMAP *img;
                sprintf(buffer, "./Monster/MONSTER_%s_%s_%d.png", dir_name[k], state_name[i], j + 1);
                img = al_load_bitmap(buffer);
                if (img)
                {
                    imgData[static_cast<MonsterDirection>(k)][static_cast<MonsterState>(i)].push_back(img);
                }
                else
                    std::cout << buffer << std::endl;
            }
        }
    }
}

void Monster::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[direction][state];

    float dx = hero_x - this->circle->x;
    float dy = hero_y - this->circle->y;
    float lenth = sqrt(dx * dx + dy * dy);

    if (dx > 0)
        direction = MonsterDirection::RIGHT;
    else
        direction = MonsterDirection::LEFT;

    if (lenth > 0)
    {
        dx /= lenth;
        dy /= lenth;
    }

    this->circle->x += dx * speed;
    this->circle->y += dy * speed;

    if (lenth < 200)
        state = MonsterState::ATTACK;
    else
        state = MonsterState::MOVE;
}

void Monster::Damaged()
{
    hp -= 1;
    std::cout << "hp: " << hp << "\n";
}

void Monster::Draw()
{
    sprite_pos = (sprite_pos >= imgCount[direction][state]) ? sprite_pos % imgCount[direction][state] : sprite_pos;
    al_draw_bitmap(imgData[direction][state][sprite_pos], this->circle->x, this->circle->y, 0);
}
