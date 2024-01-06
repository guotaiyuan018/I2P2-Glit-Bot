#include "Bullet.h"
#include <cmath>
#include <iostream>

const char bullet_name[][100] = {"ROUND", "AURABLADE", "BEAM"};

Bullet::Bullet(int mouse_x, int mouse_y, int type)
{
    this->circle = new Circle(hero_x, hero_y, 15);
    my_type = static_cast<BulletType>(type);

    if (my_type == BulletType::BEAM)
        speed = 90;

    char filename[50];
    sprintf(filename, "./Bullet/%s.png", bullet_name[type]);
    imgData = al_load_bitmap(filename);

    if (!imgData)
        std::cout << filename << std::endl;

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
    al_destroy_bitmap(imgData);
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
    bool flip = (direction_x > 0) ? true : false;
    if (my_type != BulletType::BEAM)
    {
        al_draw_bitmap(imgData, circle->x, circle->y, flip);
    }
    else
    {
        float bulletAngle = ;
        al_draw_rotated_bitmap(imgData, al_get_bitmap_width(imgData) / 2, al_get_bitmap_height(imgData) / 2,
                               circle->x, circle->y, ALLEGRO_DEGREES_TO_RADIANS(bulletAngle), flip);
    }
}
