#include "Portal.h"
#include <iostream>
using namespace std;

Portal::Portal()
{
    x = window_width / 3 * 2;
    y = window_height / 3 * 2;
    this->circle = new Circle(x, y, 128);

    port = al_load_bitmap("./Scenes/battle/portal.png");

    Draw();
}

Portal::~Portal()
{
    delete circle;

    al_destroy_bitmap(port);
}

void Portal::Draw()
{
    cout << "start to draw portal\n";
    al_draw_bitmap(port, x, y, 0);
}

