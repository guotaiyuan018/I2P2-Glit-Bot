#include "Boss.h"
#include <iostream>
#include <cmath>

const char state_name[][100] = {"ATTACK", "DEAD", "DAMAGED", "MOVE", "WAKE"};
const char dir_name[][100] = {"LEFT", "RIGHT"};

const int draw_frequency = 10;

Boss::Boss(int x, int y)
{
    this->circle = new Circle(x, y, 60);
    std::cout << "boss\n";
    imgCount[BossState::ATTACK] = 10;
    imgCount[BossState::DEAD] = 11;
    imgCount[BossState::DAMAGED] = 2;
    imgCount[BossState::MOVE] = 6;
    imgCount[BossState::WAKE] = 5;

    char buffer[50];
    for (int i = 0; i < sizeof(state_name) / sizeof(state_name[0]); i++)
    {
        for (int j = 0; j < imgCount[static_cast<BossState>(i)]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./Monster/Boss/Boss_RIGHT_%s_%d.png", state_name[i], j + 1);
            img = al_load_bitmap(buffer);
            if (img)
            {
                imgData[static_cast<BossState>(i)].push_back(img);
            }
            else
                std::cout << buffer << std::endl;
        }
    }
}

void Boss::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[state];

    float dx = hero_x - this->circle->x;
    float dy = hero_y - this->circle->y;
    float lenth = sqrt(dx * dx + dy * dy);

    if (dx > 0)
        direction = BossDirection::RIGHT;
    else
        direction = BossDirection::LEFT;

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
        state = BossState::DEAD;
        speed = 0;
    }
    else if (!start_damaged)
    {
        if (lenth < 300)
        {
            state = BossState::ATTACK;
        }

        else
        {
            state = BossState::MOVE;
            speed = 2;
        }
    }
}
void Boss::Draw()
{
    if (sprite_pos == imgCount[state] - 1 && state == BossState::DEAD)
        is_dead = true;
    if (sprite_pos == imgCount[state] - 1 && state == BossState::DAMAGED)
        start_damaged = false;

    sprite_pos = (sprite_pos >= imgCount[state]) ? sprite_pos % imgCount[state] : sprite_pos;
    bool flip_not = (direction == BossDirection::RIGHT) ? false : true;
    al_draw_bitmap(imgData[state][sprite_pos], this->circle->x - Boss_WIDTH / 2, this->circle->y - Boss_HEIGHT / 2, flip_not);
}
