#include "Monster.h"
#include <iostream>
#include <cmath>

const char state_name[][100] = {"ATTACK", "DEAD", "DAMAGED", "MOVE"};
const char dir_name[][100] = {"LEFT", "RIGHT"};
const char mon_name[][100] = {"exploder", "eyeball", "zapper"};

const int draw_frequency = 10;

Monster::Monster(int x, int y, int name)
{
    this->circle = new Circle(x - MONSTER_WIDTH / 2, y - MONSTER_HEIGHT / 2, 90);

    my_name = static_cast<MonsterName>(name);

    imgCount[MonsterName::ZAPPER][MonsterDirection::LEFT][MonsterState::ATTACK] = imgCount[MonsterName::ZAPPER][MonsterDirection::RIGHT][MonsterState::ATTACK] = 10;
    imgCount[MonsterName::ZAPPER][MonsterDirection::LEFT][MonsterState::DEAD] = imgCount[MonsterName::ZAPPER][MonsterDirection::RIGHT][MonsterState::DEAD] = 6;
    imgCount[MonsterName::ZAPPER][MonsterDirection::LEFT][MonsterState::DAMAGED] = imgCount[MonsterName::ZAPPER][MonsterDirection::RIGHT][MonsterState::DAMAGED] = 2;
    imgCount[MonsterName::ZAPPER][MonsterDirection::LEFT][MonsterState::MOVE] = imgCount[MonsterName::ZAPPER][MonsterDirection::RIGHT][MonsterState::MOVE] = 6;

    imgCount[MonsterName::EYEBALL][MonsterDirection::LEFT][MonsterState::ATTACK] = imgCount[MonsterName::EYEBALL][MonsterDirection::RIGHT][MonsterState::ATTACK] = 11;
    imgCount[MonsterName::EYEBALL][MonsterDirection::LEFT][MonsterState::DEAD] = imgCount[MonsterName::EYEBALL][MonsterDirection::RIGHT][MonsterState::DEAD] = 12;
    imgCount[MonsterName::EYEBALL][MonsterDirection::LEFT][MonsterState::DAMAGED] = imgCount[MonsterName::EYEBALL][MonsterDirection::RIGHT][MonsterState::DAMAGED] = 2;
    imgCount[MonsterName::EYEBALL][MonsterDirection::LEFT][MonsterState::MOVE] = imgCount[MonsterName::EYEBALL][MonsterDirection::RIGHT][MonsterState::MOVE] = 8;

    imgCount[MonsterName::EXPLODER][MonsterDirection::LEFT][MonsterState::ATTACK] = imgCount[MonsterName::EXPLODER][MonsterDirection::RIGHT][MonsterState::ATTACK] = 14;
    imgCount[MonsterName::EXPLODER][MonsterDirection::LEFT][MonsterState::DEAD] = imgCount[MonsterName::EXPLODER][MonsterDirection::RIGHT][MonsterState::DEAD] = 6;
    imgCount[MonsterName::EXPLODER][MonsterDirection::LEFT][MonsterState::DAMAGED] = imgCount[MonsterName::EXPLODER][MonsterDirection::RIGHT][MonsterState::DAMAGED] = 2;
    imgCount[MonsterName::EXPLODER][MonsterDirection::LEFT][MonsterState::MOVE] = imgCount[MonsterName::EXPLODER][MonsterDirection::RIGHT][MonsterState::MOVE] = 6;

    char buffer[50];
    for (int l = 0; l < sizeof(mon_name) / sizeof(mon_name[0]); l++)
    {
        for (int i = 0; i < sizeof(state_name) / sizeof(state_name[0]); i++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < imgCount[static_cast<MonsterName>(l)][static_cast<MonsterDirection>(k)][static_cast<MonsterState>(i)]; j++)
                {
                    ALLEGRO_BITMAP *img;
                    sprintf(buffer, "./Monster/%s/MONSTER_%s_%s_%d.png", mon_name[l], dir_name[k], state_name[i], j + 1);
                    img = al_load_bitmap(buffer);
                    if (img)
                    {
                        imgData[static_cast<MonsterName>(l)][static_cast<MonsterDirection>(k)][static_cast<MonsterState>(i)].push_back(img);
                    }
                    else
                        std::cout << buffer << std::endl;
                }
            }
        }
    }
}

void Monster::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[my_name][direction][state];

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

    if (hp < 0)
    {
        state = MonsterState::DEAD;
        speed = 0;
    }
}
void Monster::Draw()
{
    if (sprite_pos == imgCount[my_name][direction][state] - 1 && state == MonsterState::DEAD)
        is_dead = true;

    sprite_pos = (sprite_pos >= imgCount[my_name][direction][state]) ? sprite_pos % imgCount[my_name][direction][state] : sprite_pos;

    al_draw_bitmap(imgData[my_name][direction][state][sprite_pos], this->circle->x - MONSTER_WIDTH / 2, this->circle->y - MONSTER_HEIGHT / 2, 0);
}
