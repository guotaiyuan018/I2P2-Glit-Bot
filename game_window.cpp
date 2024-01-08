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
    glitch_timer = al_create_timer(5);
    boss_timer = al_create_timer(5);
    monster_timer = al_create_timer(1);

    if (!timer)
        show_err_msg(-1);
    if (!glitch_timer)
        show_err_msg(-1);
    if (!boss_timer)
        show_err_msg(-1);
    if (!monster_timer)
        show_err_msg(-10);

    al_init_image_addon();
    al_init_acodec_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(glitch_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(boss_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_timer));

    al_set_window_title(display, "Glit-Bot");

    game_init();
}

void game_window::game_init()
{
    icon = al_load_bitmap("./icon.png");
    load_page = al_load_bitmap("./loading.png");
    al_set_display_icon(display, icon);
    al_draw_bitmap(load_page, 0, 0, 0);
    al_flip_display();

    crosshair_cursor = al_load_bitmap("./UI/crosshair.png");
    arrow_cursor = al_load_bitmap("./UI/default.png");
    crosshair = al_create_mouse_cursor(crosshair_cursor, 0, 0);
    cursor = al_create_mouse_cursor(arrow_cursor, 0, 0);
    al_set_mouse_cursor(display, cursor);

    scene_manager = new Scene_manager();
    scene_manager->load_scenes();
}

Bullet *game_window::create_bullet(int x, int y, int type)
{
    Bullet *b = new Bullet(x, y, type);
    return b;
}

Monster *game_window::create_monster(int x, int y, int monster_type)
{
    Monster *m = new Monster(x, y, monster_type);
    return m;
}

Boss *game_window::create_boss()
{
    Boss *boss = new Boss(window_width / 2, window_height / 3);
    return boss;
}

Zone *game_window::create_zone(int init_x, int init_y)
{
    Zone *z = new Zone(init_x, init_y);
    return z;
}

void game_window::set_enemy(int stage_num)
{
    if (stage_num < 2)
    {
        for (int i = 0; i < (stage_num) * 3 + 3; i++)
        {
            int monster_type = (stage_num == 0) ? 2 : rand() % 2;

            int loc_x = rand() % window_width;
            int loc_y = rand() % window_height;

            Monster *m = create_monster(loc_x, loc_y, monster_type);
            monsterSet.emplace_back(m);
        }
    }
    else if (stage_num == 3)
    {
        Boss *boss = create_boss();
        bossSet.emplace_back(boss);
        al_start_timer(boss_timer);
    }
}

void game_window::game_begin()
{
    cur_stage = 0;
    game_won = false;

    Hero *h = new Hero();
    DC->get_Hero().emplace_front(h);

    set_enemy(cur_stage);

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

        if (healing)
            DC->get_Hero().front()->heal(counter);

        for (int i = 0; i < bulletSet.size(); i++)
        {
            bool isReachEnd = false;
            isReachEnd = bulletSet[i]->Update();

            if (isReachEnd)
            {
                bulletSet.erase(bulletSet.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < monsterSet.size(); i++)
        {
            monsterSet[i]->Update();

            bool isCollide = false;
            for (int j = 0; j < bulletSet.size(); j++)
            {
                isCollide = monsterSet[i]->getCircle()->isOverlap(monsterSet[i]->getCircle(), bulletSet[j]->getCircle());
                if (isCollide)
                {
                    monsterSet[i]->Damaged(3);

                    bulletSet.erase(bulletSet.begin() + j);
                    j--;
                }
            }

            bool isDamage = false;
            if (!isCollide)
            {
                bool isDying = monsterSet[i]->getDying();
                if (!isDying)
                    isDamage = monsterSet[i]->getCircle()->isOverlap(monsterSet[i]->getCircle(), heroSet.front()->getCircle());
                if (isDamage)
                {
                    monsterSet[i]->Damaged(100);
                    heroSet.front()->Damaged(1);
                }
            }

            bool isDead = monsterSet[i]->getDead();
            if (isDead)
            {
                monsterSet.erase(monsterSet.begin() + i);
                i--;
            }
        }
        if (!bossSet.empty())
        {
            bossSet.front()->Update();

            bool isCollide = false;
            for (int j = 0; j < bulletSet.size(); j++)
            {
                isCollide = bossSet.front()->getCircle()->isOverlap(bossSet.front()->getCircle(), bulletSet[j]->getCircle());
                if (isCollide)
                {
                    bossSet.front()->Damaged(3);

                    bulletSet.erase(bulletSet.begin() + j);
                    j--;
                }
            }

            bool isDamage = false;
            if (!isCollide)
            {
                bool isDying = bossSet.front()->getDying();
                if (!isDying)
                    isDamage = bossSet.front()->getCircle()->isOverlap(bossSet.front()->getCircle(), heroSet.front()->getCircle());
                if (isDamage)
                {
                    // bossSet.front()->Damaged(1);
                    heroSet.front()->Damaged(1);
                }
            }

            bool isDead = bossSet.front()->getDead();
            if (isDead)
            {
                bossSet.erase(bossSet.begin());
                zoneSet.clear();
                al_stop_timer(boss_timer);
            }
        }

        if (cur_stage < 2)
        {
            if (monsterSet.empty())
                stage_clear = true;
            else
                stage_clear = false;
        }
        else if (cur_stage == 3)
        {
            if (bossSet.empty())
                stage_clear = true;
            else
                stage_clear = false;
        }
        else
            stage_clear = false; // implement the boss stage clear logic here

        if (cur_stage < STAGE_NUM)
        {
            if (cur_stage == 2 || stage_clear)
            {
                if (!portal)
                    portal = new Portal();
                enter_portal = portal->getCircle()->isOverlap(portal->getCircle(), heroSet.front()->getCircle());

                if (enter_portal)
                {
                    enter_portal = false;
                    cur_stage++;
                    loading = true;
                    load_next = true;

                    delete portal;
                    portal = NULL;
                }
            }
        }
        else if (cur_stage == 3)
        {
            if (stage_clear)
            {
                if (!portal)
                    portal = new Portal();
                enter_portal = portal->getCircle()->isOverlap(portal->getCircle(), heroSet.front()->getCircle());

                if (enter_portal)
                {
                    enter_portal = false;
                    game_won = true;
                    scene_manager->change_scene();

                    delete portal;
                    portal = NULL;
                }
            }
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
        if (event.timer.source == timer)
        {
            frame_update = true;
            counter = (counter + 1);

            if (cur_scene == BATTLE_SCENE && !al_get_timer_started(glitch_timer))
            {
                al_start_timer(glitch_timer);
            }

            if (load_next)
            {
                std::cout << "stage:" << cur_stage << std::endl;
                if (cur_stage != 2 && cur_stage <= STAGE_NUM)
                    set_enemy(cur_stage);
                al_start_timer(monster_timer);
            }
            loading = false;
            load_next = false;
        }
        else if (event.timer.source == glitch_timer)
        {
            if (rand() % 100)
                heroSet.front()->Glitch(rand() % 3);
        }
        else if (event.timer.source == boss_timer)
        {
            bossSet.front()->Attack(hero_x, hero_y);

            if (zoneSet.empty())
            {
                zoneSet.emplace_back(create_zone(hero_x, hero_y));
            }
            else
                zoneSet.clear();
        }
        else if (event.timer.source == monster_timer)
        {
            al_stop_timer(monster_timer);
            for (auto s : monsterSet)
                s->Go();
        }
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
            scene_manager->change_scene();

            if (exit_game)
            {
                game_mute = true;
                game_destroy();
            }
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
            if (!start_atk)
            {
                heroSet.front()->Attack();
                Bullet *t = game_window::create_bullet(mouse_x, mouse_y, heroSet.front()->getNAME());
                bulletSet.push_back(t);
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

    if (loading)
    {
        al_draw_bitmap(load_page, 0, 0, 0);
    }
    else
    {
        scene_manager->draw_background(counter);

        if (cur_scene == BATTLE_SCENE)
        {
            al_set_mouse_cursor(display, crosshair);

            if (stage_clear || cur_stage == 2)
            {
                portal->Draw();
            }

            if (!zoneSet.empty())
                zoneSet.front()->Draw();

            for (vector<Bullet *>::iterator it = bulletSet.begin(); it != bulletSet.end(); it++)
                (*it)->Draw();

            for (vector<Monster *>::iterator it = monsterSet.begin(); it != monsterSet.end(); it++)
                (*it)->Draw();

            heroSet.front()->Draw();

            if (!bossSet.empty())
                bossSet.front()->Draw();
        }
        else
            al_set_mouse_cursor(display, cursor);

        scene_manager->draw_ui();
    }

    al_flip_display();
}

void game_window::game_reset()
{
    al_stop_timer(timer);
    frame_update = false;
    scene_manager->reset();

    monsterSet.clear();

    cur_stage = 0;
    game_won = false;
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
    delete portal;

    cout << "Game Destroyed.\n";
}
