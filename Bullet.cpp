#include "Bullet.h"
#include <cmath>
#include <iostream>

const char bullet_name[][100] = {"ROUND", "AURABLADE"};

Bullet::Bullet(int mouse_x, int mouse_y, int type)
{
    this->circle = new Circle(hero_x, hero_y, 15);
    my_type = static_cast<BulletType>(type);
    for (int i = 0; i < bullet_num; i++)
    {
        char filename[50];
        sprintf(filename, "./Bullet/%s.png", bullet_name[i]);
        imgData[static_cast<BulletType>(i)] = al_load_bitmap(filename);
    }

    float dx = mouse_x - hero_x, dy = mouse_y - hero_y;
    float lenth = sqrt(dx * dx + dy * dy);
    if (lenth > 0)
        dx /= lenth, dy /= lenth;
    direction_x = dx, direction_y = dy;

    // std::cout << "direction_x: " << direction_x << " direction_y: " << direction_y << std::endl;
}

Bullet::~Bullet()
{
    delete circle;
    for (auto s : imgData)
        al_destroy_bitmap(s.second);
}

bool Bullet::Update()
{
    circle->x += direction_x * speed;
    circle->y += direction_y * speed;
    // std::cout << "x: " << circle->x << " y: " << circle->y << std::endl;
    bool OutOfRange = false;
    if (circle->x > window_width || circle->x < 0 || circle->y > window_height || circle->y < 0)
        OutOfRange = true;
    return OutOfRange;
}

void Bullet::Draw()
{
    al_draw_bitmap(imgData[my_type], circle->x, circle->y, 0);
}
