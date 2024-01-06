#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <stdio.h>
#include <utility>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"

enum class BulletType
{
    ROUND,
    AURABLADE
};

class Bullet : public Object
{
public:
    Bullet(int, int, int);
    ~Bullet();

    bool Update();
    void Draw();
    bool attack();

protected:
    int speed = 15;
    float direction_x, direction_y;
    int bullet_num = 2;
    BulletType my_type = BulletType::ROUND;
    std::map<BulletType, ALLEGRO_BITMAP *> imgData;
};

#endif
