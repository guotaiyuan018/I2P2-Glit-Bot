#ifndef ZONE_H_INCLUDED
#define ZONE_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <map>
#include "Object.h"
#include "Circle.h"
#include "global.h"

class Zone : public Object
{
public:
    Zone(int, int);
    void Draw();

private:
    int ZONE_WIDTH = 412, ZONE_HEIGHT = 165;
    ALLEGRO_BITMAP *imgData;
};

#endif
