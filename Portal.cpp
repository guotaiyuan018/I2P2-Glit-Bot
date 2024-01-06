#include "Portal.h"
#include <iostream>
using namespace std;

Portal::Portal()
{
    x = window_width / 3 * 2;
    y = window_height / 2;
    this->circle = new Circle(x, y, 128);

    port = al_load_bitmap("./Scenes/battle/portal.png");
}

Portal::~Portal()
{
    delete circle;

    al_destroy_bitmap(port);
}

void Portal::Draw()
{
    al_draw_bitmap(port, x, y, 0);
}

