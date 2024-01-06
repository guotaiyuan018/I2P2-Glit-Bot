#include "game_window.h"
#include "DataCenter.h"
#include <iostream>

using namespace std;

game_window::game_window()
{
    if (!al_init())
        show_err_msg(-1);
    cout << "Game loading...\n";

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    if (!timer)
        show_err_msg(-1);

    al_init_image_addon();
    al_init_acodec_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_set_window_title(display, "Glit-Bot");

    game_init();
}

void game_window::game_init()
{
    icon = al_load_bitmap("./icon.png");
    loading = al_load_bitmap("./loading.png");
    al_set_display_icon(display, icon);
    al_draw_bitmap(loading, 0, 0, 0);
    al_flip_display();

    crosshair_cursor = al_load_bitmap("./UI/crosshair.png");
    arrow_cursor = al_load_bitmap("./UI/default.png");
    crosshair = al_create_mouse_cursor(crosshair_cursor, 0, 0);
    cursor = al_create_mouse_cursor(arrow_cursor, 0, 0);
    al_set_mouse_cursor(display, cursor);

    scene_manager = new Scene_manager();
    scene_manager->load_scenes();
}

Bullet *game_window::create_bullet(int x, int y)
{
    Bullet *b = new Bullet(x, y);
    return b;
}

Monster *game_window::create_monster(int x, int y)
{
    Monster *m = new Monster(x, y);
    return m;
}

void game_window::set_enemy()
{
    for (int i = window_width * 3 / 4; i < window_width; i += window_width / 4)
    {
        Monster *m = create_monster(i, window_height / 4);
        monsterSet.emplace_back(m);
    }
}

void game_window::game_begin()
{

    cur_stage = 0;

    Hero *h = new Hero();
    DC->get_Hero().emplace_front(h);

    set_enemy();

    al_flip_display();
    al_start_timer(timer);
    draw_scene();
}

void game_window::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;

    game_begin();

    while (msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void game_window::show_err_msg(int msg)
{
    if (msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d\n", msg);

    game_destroy();
    exit(9);
}

int game_window::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue))
    {
        error = process_event();
    }

    return error;
}

int game_window::game_update()
{
    if (cur_scene == BATTLE_SCENE)
    {
        DC->get_Hero().front()->Update();
        for (int i = 0; i < bulletSet.size(); i++)
        {
            bool isDestroyed = false, isReachEnd = false;
            isReachEnd = bulletSet[i]->Update();

            if (isReachEnd)
            {
                bulletSet.erase(bulletSet.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < monsterSet.size(); i++)
        {
            bool isCollide = false;
            monsterSet[i]->Update();
            for (int j = 0; j < bulletSet.size(); j++)
            {
                isCollide = monsterSet[i]->getCircle()->isOverlap(monsterSet[i]->getCircle(), bulletSet[j]->getCircle());
                if (isCollide)
                {
                    std::cout << "m_x: " << monsterSet[i]->getCircle()->x << " m_y: " << monsterSet[i]->getCircle()->y << std::endl;
                    std::cout << "b_x: " << bulletSet[j]->getCircle()->x << " b_y: " << bulletSet[j]->getCircle()->y << std::endl;
                    bool isDead = false;

                    monsterSet[i]->Damaged();

                    if (monsterSet[i]->getHP() < 0)
                        isDead = true;

                    if (isDead)
                    {
                        monsterSet.erase(monsterSet.begin() + i);
                        i--;
                    }

                    bulletSet.erase(bulletSet.begin() + j);
                    j--;
                }
            }
        }
        if (monsterSet.empty())
            stage_clear = true;
        else
            stage_clear = false;

        if (stage_clear && cur_stage < STAGE_NUM)
        {
            cur_stage++;
            set_enemy();
        }
    }
    return GAME_CONTINUE;
}

int game_window::process_event()
{
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    frame_update = false;

    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        frame_update = true;
        anime_counter = (anime_counter + 1) % title_frames;
    }
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.mouse.button == 1)
        {
            mouse_down = true;
            heroSet.front()->Glitch();
            scene_manager->change_scene();
            if (exit_game)
                game_destroy();
            if (reset_game)
                game_reset();
        }
    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        mouse_down = false;
    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        scene_manager->mouse_in(mouse_x, mouse_y);
    }
    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        key_state[event.keyboard.keycode] = true;
        scene_manager->key_in();
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        key_state[event.keyboard.keycode] = false;
        scene_manager->key_in();
    }

    if (cur_scene == BATTLE_SCENE)
    {
        if (mouse_down)
        {
            if (fired)
            {
                if (!shooted)
                {
                    Bullet *t = game_window::create_bullet(mouse_x, mouse_y);
                    bulletSet.push_back(t);
                    shooted = true;
                }
            }
        }
    }

    if (frame_update)
    {
        instruction = game_update();

        draw_scene();
        frame_update = false;
    }

    return instruction;
}

void game_window::draw_scene()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));

    scene_manager->draw_background(get_anime_counter());

    if (cur_scene == BATTLE_SCENE)
    {
        al_set_mouse_cursor(display, crosshair);

        for (vector<Bullet *>::iterator it = bulletSet.begin(); it != bulletSet.end(); it++)
            (*it)->Draw();

        for (vector<Monster *>::iterator it = monsterSet.begin(); it != monsterSet.end(); it++)
            (*it)->Draw();

        DC->get_Hero().front()->Draw();
    }
    else
        al_set_mouse_cursor(display, cursor);

    scene_manager->draw_ui();

    al_flip_display();
}

void game_window::game_reset()
{
    reset_game = false;
    monsterSet.clear();
    scene_manager->reset();

    al_stop_timer(timer);
    frame_update = false;
    reset_game = false;

    game_begin();
}

void game_window::game_destroy()
{
    cout << "Exit game...\n";

    game_reset();
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    al_destroy_bitmap(crosshair_cursor);
    al_destroy_bitmap(arrow_cursor);
    al_destroy_mouse_cursor(crosshair);
    al_destroy_mouse_cursor(cursor);

    delete scene_manager;

    cout << "Game Destroyed.\n";
}
