#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <map>

#define DEFAULT 0
#define HOVERED 1

class Button
{
public:
    Button();
    ~Button();

    void Draw();

    // plar sfx and react mouse hover
    void mouse_act();
    void key_act();

private:
    map<array<int, 2>, array<int, 2>> position;
    ALLEGRO_BITMAP* image[2];

};
#endif // BUTTON_H_INCLUDED
