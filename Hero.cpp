#include "Hero.h"
#include <iostream>

const char dir_name[][100] = {"LEFT", "RIGHT"};
const char state_name[][100] = {"MOVE", "IDLE", "ATTACK", "GLITCH"};
const char hero_name[][100] = {"BULLET", "BLADE"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Hero::Hero()
{
    this->circle = new Circle(window_width / 2, window_height / 2, 128);

    imgCount[HeroDirection::LEFT][HeroState::MOVE] = 8;
    imgCount[HeroDirection::LEFT][HeroState::IDLE] = 2;
    imgCount[HeroDirection::LEFT][HeroState::ATTACK] = 4;
    imgCount[HeroDirection::LEFT][HeroState::GLITCH] = 5;
    imgCount[HeroDirection::RIGHT][HeroState::MOVE] = 8;
    imgCount[HeroDirection::RIGHT][HeroState::IDLE] = 2;
    imgCount[HeroDirection::RIGHT][HeroState::ATTACK] = 4;
    imgCount[HeroDirection::RIGHT][HeroState::GLITCH] = 5;

    char buffer[50];

    for (int i = 0; i < sizeof(hero_name) / sizeof(hero_name[0]); i++)
    {
        for (int l = 0; l < sizeof(dir_name) / sizeof(dir_name[0]); l++)
        {
            for (int k = 0; k < sizeof(state_name) / sizeof(state_name[0]); k++)
            {
                for (int j = 0; j < imgCount[static_cast<HeroDirection>(l)][static_cast<HeroState>(k)]; j++)
                {
                    ALLEGRO_BITMAP *img;
                    sprintf(buffer, "./Hero/%s/HERO_%s_%s_%d.png", hero_name[i], dir_name[l], state_name[k], j + 1);
                    img = al_load_bitmap(buffer);
                    if (img)
                    {
                        imgData[static_cast<HeroName>(i)][static_cast<HeroDirection>(l)][static_cast<HeroState>(k)].push_back(img);
                    }
                    else
                        std::cout << buffer << std::endl;
                }
            }
        }
    }
}

void Hero::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[direction][state];

    if (key_state[ALLEGRO_KEY_W])
    {
        if (circle->y > -100)
        {
            circle->y -= speed;
            state = HeroState::MOVE;
        }
    }
    if (key_state[ALLEGRO_KEY_S])
    {
        if (circle->y < 700)
        {
            circle->y += speed;
            state = HeroState::MOVE;
        }
    }
    if (key_state[ALLEGRO_KEY_A])
    {
        if (circle->x > -100)
        {
            circle->x -= speed;
            state = HeroState::MOVE;
        }
    }
    if (key_state[ALLEGRO_KEY_D])
    {
        if (circle->x < 1000)
        {
            circle->x += speed;
            state = HeroState::MOVE;
        }
    }

    if (mouse_down)
    {
        state = HeroState::ATTACK;
    }

    if (!key_state[ALLEGRO_KEY_W] && !key_state[ALLEGRO_KEY_A] && !key_state[ALLEGRO_KEY_S] && !key_state[ALLEGRO_KEY_D] && !mouse_down)
        state = HeroState::IDLE;

    if (circle->x > mouse_x)
        direction = HeroDirection::LEFT;
    else
        direction = HeroDirection::RIGHT;

    if (!mouse_down)
        fired = true, shooted = false;

    hero_x = circle->x, hero_y = circle->y;
}

void Hero::Draw()
{
    sprite_pos = (sprite_pos >= imgCount[direction][state]) ? sprite_pos % imgCount[direction][state] : sprite_pos;
    if (state == HeroState::ATTACK)
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
    al_draw_bitmap(imgData[my_name][direction][state][sprite_pos], circle->x, circle->y, 0);
}
