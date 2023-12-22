#include "Hero.h"
#include <iostream>

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][100] = {"LEFT_MOVE", "RIGHT_MOVE"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Hero::Hero()
{
    imgCount[HeroState::LEFT_MOVE] = 8;
    imgCount[HeroState::RIGHT_MOVE] = 8;
    // imgCount[HeroState::LEFT_IDLE] = 4;
    // imgCount[HeroState::RIGHT_IDLE] = 4;

    char buffer[50];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < imgCount[static_cast<HeroState>(i)]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./srcs/Hero/HERO_%s_%d.png", direction_name[i], j + 1);
            img = al_load_bitmap(buffer);
            if (img)
                imgData[static_cast<HeroState>(i)].push_back(img);

            else
                std::cout << buffer << std::endl;
        }
    }

    // sprintf(buffer, "./Bullet/bullet.png");
    // imgData = al_load_bitmap(buffer);

    x = window_width / 2;
    y = window_height / 2;
}

void Hero::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[direction];

    if (key_state[ALLEGRO_KEY_W])
    {
        y -= speed;
        if (key_state[ALLEGRO_KEY_A])
        {
            x -= speed;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            x += speed;
        }
    }
    else if (key_state[ALLEGRO_KEY_A])
    {
        x -= speed;
        direction = HeroState::RIGHT_MOVE;
        if (key_state[ALLEGRO_KEY_W])
        {
            y -= speed;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            y += speed;
        }
    }
    else if (key_state[ALLEGRO_KEY_S])
    {
        y += speed;
        if (key_state[ALLEGRO_KEY_A])
        {
            x -= speed;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            x += speed;
        }
    }
    else if (key_state[ALLEGRO_KEY_D])
    {
        x += speed;
        direction = HeroState::LEFT_MOVE;
        if (key_state[ALLEGRO_KEY_W])
        {
            y -= speed;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            y += speed;
        }
    }
    /*
    else
    {
        if (direction == HeroState::LEFT_MOVE)
            direction = HeroState::LEFT_IDLE;
        else if (direction == HeroState::RIGHT_MOVE)
            direction = HeroState::RIGHT_IDLE;
    }
    */
}

void Hero::Draw()
{

    al_draw_bitmap(imgData[direction][sprite_pos], x, y, 0);

    // al_draw_bitmap(imgData, x, y, 0);
}

std::pair<int, int> Hero::Pos()
{
    return std::make_pair(x, y);
}
