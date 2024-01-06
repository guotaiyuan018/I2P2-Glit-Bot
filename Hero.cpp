#include "Hero.h"
#include <iostream>

const char dir_name[][100] = {"LEFT", "RIGHT"};
const char state_name[][100] = {"MOVE", "IDLE", "ATTACK", "GLITCH", "DAMAGED"};
const char hero_name[][100] = {"BULLET", "BLADE", "BEAM"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Hero::Hero()
{
    this->circle = new Circle(window_width / 2, window_height / 2, 20);

    imgCount[HeroDirection::LEFT][HeroState::MOVE] = 8;
    imgCount[HeroDirection::LEFT][HeroState::IDLE] = 2;
    imgCount[HeroDirection::LEFT][HeroState::ATTACK] = 4;
    imgCount[HeroDirection::LEFT][HeroState::GLITCH] = 5;
    imgCount[HeroDirection::LEFT][HeroState::DAMAGED] = 6;
    imgCount[HeroDirection::RIGHT][HeroState::MOVE] = 8;
    imgCount[HeroDirection::RIGHT][HeroState::IDLE] = 2;
    imgCount[HeroDirection::RIGHT][HeroState::ATTACK] = 4;
    imgCount[HeroDirection::RIGHT][HeroState::GLITCH] = 5;
    imgCount[HeroDirection::RIGHT][HeroState::DAMAGED] = 6;

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
    x = this->circle->x;
    y = this->circle->y;

    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[direction][state];

    if (!start_glitch)
    {
        if (start_atk || start_damaged)
        {
            if (key_state[ALLEGRO_KEY_W])
            {
                if (y > 0)
                {
                    this->circle->y -= speed;
                }
            }
            if (key_state[ALLEGRO_KEY_S])
            {
                if (y < window_height)
                {
                    this->circle->y += speed;
                }
            }
            if (key_state[ALLEGRO_KEY_A])
            {
                if (x > 0)
                {
                    this->circle->x -= speed;
                }
            }
            if (key_state[ALLEGRO_KEY_D])
            {
                if (x < window_width)
                {
                    this->circle->x += speed;
                }
            }
        }
        else
        {
            if (key_state[ALLEGRO_KEY_LSHIFT])
                speed = 7;
            else
                speed = 5;

            if (key_state[ALLEGRO_KEY_W])
            {
                if (y > 0)
                {
                    this->circle->y -= speed;
                }
            }
            if (key_state[ALLEGRO_KEY_S])
            {
                if (y < window_height)
                {
                    this->circle->y += speed;
                }
            }
            if (key_state[ALLEGRO_KEY_A])
            {
                if (x > 0)
                {
                    this->circle->x -= speed;
                    if (!start_damaged)
                        state = HeroState::MOVE;
                }
            }
            if (key_state[ALLEGRO_KEY_D])
            {
                if (x < window_width)
                {
                    this->circle->x += speed;
                    if (!start_damaged)
                        state = HeroState::MOVE;
                }
            }

            if (!key_state[ALLEGRO_KEY_W] && !key_state[ALLEGRO_KEY_A] && !key_state[ALLEGRO_KEY_S] && !key_state[ALLEGRO_KEY_D] && !mouse_down)
                state = HeroState::IDLE;
        }

        if (x > mouse_x)
            direction = HeroDirection::LEFT;
        else
            direction = HeroDirection::RIGHT;
    }

    hero_x = x, hero_y = y;
    // hero_x = x, hero_y = y;
}

void Hero::Glitch(int name)
{
    if (my_name != static_cast<HeroName>(name))
    {
        my_name = static_cast<HeroName>(name);
        state = HeroState::GLITCH;
        sprite_pos = 0;
        start_glitch = true;
        start_glitch = false;
        start_atk = false;
    }
}

void Hero::Attack()
{
    state = HeroState::ATTACK;
    sprite_pos = 0;
    start_atk = true;
}

void Hero::Draw()
{

    if (sprite_pos == imgCount[direction][state] - 1)
    {
        if (state == HeroState::GLITCH && start_glitch)
        {
            state = HeroState::IDLE;
            start_glitch = false;
        }
        if (state == HeroState::ATTACK && start_atk)
        {
            state = HeroState::IDLE;
            start_atk = false;
        }
        if (state == HeroState::DAMAGED && start_damaged)
        {
            state = HeroState::IDLE;
            start_damaged = false;
        }
    }

    sprite_pos = (sprite_pos >= imgCount[direction][state]) ? sprite_pos % imgCount[direction][state] : sprite_pos;

    al_draw_bitmap(imgData[my_name][direction][state][sprite_pos], x - HERO_WIDTH / 2, y - HERO_HEIGHT / 2, 0);
}