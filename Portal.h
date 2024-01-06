#ifndef PORTAL_H_INCLUDED
#define PORTAL_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"

#define PORTAL_WIDTH 171
#define PORTAL_HEIGHT 193

class Portal : public Object
{
public:
    Portal();
    ~Portal();

    void Draw();

private:
    int x, y;
    ALLEGRO_BITMAP* port = NULL;
};
#endif // PORTAL_H_INCLUDED
