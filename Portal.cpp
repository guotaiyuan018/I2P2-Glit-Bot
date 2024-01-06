#include "Portal.h"
#include <iostream>
using namespace std;

Portal::Portal()
{
    x = window_width / 3 * 2;
    y = window_height / 2;
    this->circle = new Circle(x, y + PORTAL_HEIGHT / 4, 20);

    port = al_load_bitmap("./Scenes/battle/portal.png");
}

Portal::~Portal()
{
    delete circle;

    al_destroy_bitmap(port);
}

void Portal::Draw()
{
    al_draw_bitmap(port, x - PORTAL_WIDTH / 2, y - PORTAL_HEIGHT / 2, 0);
}

