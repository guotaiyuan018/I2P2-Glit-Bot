#include "Bullet.h"
#include <cmath>
#include <iostream>

Bullet::Bullet(int mouse_x, int mouse_y, int init_x, int init_y)
{
    this->circle = new Circle(init_x, init_y, 10);

    char filename[50];
    sprintf(filename, "./srcs/Bullet/bullet.png");
    img = al_load_bitmap(filename);

    float dx = mouse_x - init_x, dy = mouse_y - init_y;
    float lenth = sqrt(dx * dx + dy * dy);
    if (lenth > 0)
        dx /= lenth, dy /= lenth;
    direction_x = dx, direction_y = dy;

    std::cout << "direction_x: " << direction_x << " direction_y: " << direction_y << std::endl;
}

Bullet::~Bullet()
{
    delete circle;

    al_destroy_bitmap(img);
}

void Bullet::Update()
{
    circle->x += direction_x * speed;
    circle->y += direction_y * speed;
    std::cout << "x: " << circle->x << " y: " << circle->y << std::endl;
}

void Bullet::Draw()
{
    al_draw_bitmap(img, circle->x, circle->y, 0);
}
