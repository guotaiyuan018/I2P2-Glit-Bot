#include "Hero.h"
#include <iostream>

const char direction_name[][100] = {"LEFT_MOVE", "RIGHT_MOVE", "LEFT_IDLE", "RIGHT_IDLE", "LEFT_ATTACK", "RIGHT_ATTACK"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Hero::Hero()
{
    imgCount[HeroState::LEFT_MOVE] = 8;
    imgCount[HeroState::RIGHT_MOVE] = 8;
    imgCount[HeroState::LEFT_IDLE] = 2;
    imgCount[HeroState::RIGHT_IDLE] = 2;
    imgCount[HeroState::LEFT_ATTACK] = 4;
    imgCount[HeroState::RIGHT_ATTACK] = 4;

    char buffer[50];

    for (int i = 0; i < sizeof(direction_name) / sizeof(direction_name[0]); i++)
    {
        for (int j = 0; j < imgCount[static_cast<HeroState>(i)]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./Hero/bullet/HERO_%s_%d.png", direction_name[i], j + 1);
            img = al_load_bitmap(buffer);
            if (img)
            {
                imgData[static_cast<HeroState>(i)].push_back(img);
            }
            else
                std::cout << buffer << std::endl;
        }
    }

    x = window_width / 2;
    y = window_height / 2;
}

void Hero::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[direction];

    if (mouse_down)
    {
        if (direction == HeroState::LEFT_IDLE || direction == HeroState::LEFT_MOVE)
            direction = HeroState::LEFT_ATTACK;
        else if (direction == HeroState::RIGHT_IDLE || direction == HeroState ::RIGHT_MOVE)
            direction = HeroState::RIGHT_ATTACK;

        if (key_state[ALLEGRO_KEY_W])
        {
            y -= speed;
        }
        if (key_state[ALLEGRO_KEY_S])
        {
            y += speed;
        }
        if (key_state[ALLEGRO_KEY_A])
        {
            x -= speed;
        }
        if (key_state[ALLEGRO_KEY_D])
        {
            x += speed;
        }
    }
    else if (!key_state[ALLEGRO_KEY_W] & !key_state[ALLEGRO_KEY_S] & !key_state[ALLEGRO_KEY_A] & !key_state[ALLEGRO_KEY_D])
    {
        if (direction == HeroState::LEFT_MOVE || direction == HeroState::LEFT_ATTACK)
            direction = HeroState::LEFT_IDLE;
        else if (direction == HeroState::RIGHT_MOVE || direction == HeroState::RIGHT_ATTACK)
            direction = HeroState::RIGHT_IDLE;
    }
    else
    {
        if (key_state[ALLEGRO_KEY_W])
        {
            y -= speed;
            if (direction == HeroState::LEFT_ATTACK || direction == HeroState::LEFT_IDLE)
                direction = HeroState::LEFT_MOVE;
            else if (direction == HeroState::RIGHT_ATTACK || direction == HeroState::RIGHT_IDLE)
                direction = HeroState::RIGHT_MOVE;
        }
        if (key_state[ALLEGRO_KEY_S])
        {
            y += speed;
            if (direction == HeroState::LEFT_ATTACK || direction == HeroState::LEFT_IDLE)
                direction = HeroState::LEFT_MOVE;
            else if (direction == HeroState::RIGHT_ATTACK || direction == HeroState::RIGHT_IDLE)
                direction = HeroState::RIGHT_MOVE;
        }
        if (key_state[ALLEGRO_KEY_A])
        {
            x -= speed;
            direction = HeroState::LEFT_MOVE;
        }
        if (key_state[ALLEGRO_KEY_D])
        {
            x += speed;
            direction = HeroState::RIGHT_MOVE;
        }
    }
    if (!mouse_down)
        fired = true, shooted = false;

    hero_x = this->x, hero_y = this->y;
}

void Hero::Draw()
{
    sprite_pos = (sprite_pos >= imgCount[direction]) ? sprite_pos % imgCount[direction] : sprite_pos;
    if (direction == HeroState::LEFT_ATTACK || direction == HeroState::RIGHT_ATTACK)
    {
        if (sprite_pos == 0)
        {
            fired = true;
        }
        else
        {
            fired = false;
            shooted = false;
        }
    }
    al_draw_bitmap(imgData[direction][sprite_pos], x, y, 0);
}
