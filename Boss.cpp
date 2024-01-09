#include "Boss.h"
#include <iostream>
#include <cmath>

const char state_name[][100] = {"ATTACK", "DEAD", "DAMAGED", "MOVE", "WAKE"};
const char dir_name[][100] = {"LEFT", "RIGHT"};

Boss::Boss(int x, int y)
{
    draw_frequency = 60;
    speed = 0;
    state = BossState::WAKE;

    this->circle = new Circle(x, y, 150);
    // std::cout << "boss\n";
    imgCount[BossState::ATTACK] = 10;
    imgCount[BossState::DEAD] = 11;
    imgCount[BossState::DAMAGED] = 6;
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

    al_reserve_samples(1);
    sample = al_load_sample("./audio/roar.wav");
    roar = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(roar, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(roar, al_get_default_mixer());
    al_set_sample_instance_gain(roar, 0.3);
}

void Boss::Update()
{
    counter = (counter + 1) % draw_frequency;
    if (counter == 0)
        sprite_pos = (sprite_pos + 1) % imgCount[state];

    float dx = hero_x - this->circle->x;
    float dy = hero_y - this->circle->y;
    float lenth = sqrt(dx * dx + dy * dy);

    if (!start_death)
    {
        if (dx > 0)
            direction = BossDirection::RIGHT;
        else
            direction = BossDirection::LEFT;
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
        state = BossState::DEAD;
        speed = 0;
    }
}

void Boss::Attack(int x, int y)
{
    if (!is_dead)
    {
        if (!start_atk)
        {
            state = BossState::MOVE;
            sprite_pos = 0;
            speed = 0;
            start_atk = true;
            freeze = false;
        }
        else
        {
            atk_x = hero_x, atk_y = hero_y;
            state = BossState::ATTACK;
            sprite_pos = 0;

            if (al_get_sample_instance_playing(roar))
                al_stop_sample_instance(roar);
            if (!game_mute)
                al_play_sample_instance(roar);
            freeze = true;
        }
    }
}

void Boss::Draw()
{

    if (sprite_pos == imgCount[state] - 1 && state == BossState::DEAD)
        is_dead = true;
    if (sprite_pos == imgCount[state] - 1 && state == BossState::DAMAGED)
        start_damaged = false, state = BossState::MOVE;
    if (sprite_pos == imgCount[state] - 1 && state == BossState::WAKE)
    {
        state = BossState::MOVE;
        draw_frequency = 10;
        speed = 3;
    }
    if (sprite_pos == imgCount[state] - 1 && state == BossState::ATTACK)
    {
        state = BossState::MOVE;
        start_atk = false;
        speed = 3;
        freeze = false;
    }

    if (sprite_pos == 4 && state == BossState::ATTACK)
        this->circle->x = atk_x, this->circle->y = atk_y;

    sprite_pos = (sprite_pos >= imgCount[state]) ? sprite_pos % imgCount[state] : sprite_pos;
    bool flip_not = (direction == BossDirection::RIGHT) ? false : true;
    al_draw_bitmap(imgData[state][sprite_pos], this->circle->x - Boss_WIDTH / 2, this->circle->y - Boss_HEIGHT / 2, flip_not);
}
