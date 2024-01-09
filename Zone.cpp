#include "Zone.h"
#include <iostream>

Zone::Zone(int init_x, int init_y)
{
    this->circle = new Circle(init_x, init_y, 200);

    char buffer[50];
    sprintf(buffer, "./attack_zone.png");
    imgData = al_load_bitmap(buffer);
}

void Zone::Draw()
{
    al_draw_bitmap(imgData, hero_x - ZONE_WIDTH / 2, hero_y - ZONE_HEIGHT / 2, 0);
}