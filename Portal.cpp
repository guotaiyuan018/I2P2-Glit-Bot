#include "Portal.h"
#include <iostream>
using namespace std;

Portal::Portal()
{
    int add = rand() % 2;
    int rx = rand() % 200 + 50;
    int ry = rand() % 200 + 50;

    x = hero_x + (add ? rx : -rx);
    y = hero_y + (add ? ry : -ry);

    if(x >= 700) x /= 2;
    else if(x <= 300) x *= 2;
    if(y >= 500) y /= 2;
    else if(y <= 200)
    {
        if(y <= 50) y = 100;
        else
        {
            y *= 2;
        }
    }

    this->circle = new Circle(x, y + 20, 30);

    port = al_load_bitmap("./Scenes/battle/portal.png");

}

Portal::~Portal()
{
    delete circle;

    al_destroy_bitmap(port);

}

void Portal::Draw()
{
    if(cur_stage == 2) {
        this->circle->x = window_width / 4 * 3;
        this->circle->y = window_height / 2 - 20;
        al_draw_bitmap(port, this->circle->x - PORTAL_WIDTH / 2, this->circle->y - PORTAL_HEIGHT / 2, 0);
    }
    else if(cur_stage == 3){
        this->circle->x = window_width / 2;
        this->circle->y = window_height / 2;
        al_draw_bitmap(port, this->circle->x - PORTAL_WIDTH / 2, this->circle->y - PORTAL_HEIGHT / 2, 0);
    }
    else al_draw_bitmap(port, x - PORTAL_WIDTH / 2, y - PORTAL_HEIGHT / 2, 0);
}

