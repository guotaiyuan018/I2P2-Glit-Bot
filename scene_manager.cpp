#include "scene_manager.h"
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

Scene_manager::Scene_manager()
{
    current_scene = 0;
    prev_scene = current_scene;
    title_scene = new Title_scene();
    game_scene = new Game_scene();
    setting_scene = new Setting_scene();
    // end_scene = new End_scene();
}

void Scene_manager::load_scenes()
{
    al_reserve_samples(10);
    title_scene->load_scene();
    game_scene->load_scene();
    setting_scene->load_scene();
    // end_scene->load_scene();

    credit_scene = al_load_bitmap("./Scenes/credit.png");

    // audio
    sample = al_load_sample("./audio/title.wav");
    title_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(title_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(title_bgm, al_get_default_mixer());

    sample = al_load_sample("./audio/game.mp3");
    game_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(game_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(game_bgm, al_get_default_mixer());
}

void Scene_manager::draw_background(int anime_counter)
{
    // cout << "start to draw scene: " << scene << endl;
    switch (current_scene)
    {
    case TITLE_SCENE:
        // audio
        if (al_get_sample_instance_playing(game_bgm))
            al_stop_sample_instance(game_bgm);

        if (!game_mute)
        {
            al_set_sample_instance_gain(title_bgm, 1);
            al_play_sample_instance(title_bgm);
        }
        else
            al_stop_sample_instance(title_bgm);

        // visual
        title_scene->draw_background(anime_counter);
        break;

    case BATTLE_SCENE:
        // audio
        if (al_get_sample_instance_playing(title_bgm))
            al_stop_sample_instance(title_bgm);

        if (!game_mute)
        {
            al_set_sample_instance_gain(game_bgm, 1);
            al_play_sample_instance(game_bgm);
        }
        else
            al_stop_sample_instance(game_bgm);

        // visual
        game_scene->draw_background();
        break;

    case SET_SCENE:
        // audio
        if (game_mute)
        {
            al_set_sample_instance_gain(title_bgm, 0);
            al_set_sample_instance_gain(game_bgm, 0);
        }
        else
        {
            switch (prev_scene)
            {
            case TITLE_SCENE:
                al_set_sample_instance_gain(title_bgm, 1);
                break;
            case BATTLE_SCENE:
                al_set_sample_instance_gain(game_bgm, 1);
                break;
            }
        }

        // visual
        setting_scene->draw_background();
        break;

    case CREDIT_SCENE:
        al_draw_bitmap(credit_scene, 0, 0, 0);
        break;
    }
    // cout << "draw scene finish\n";
}

void Scene_manager::draw_ui()
{
    switch (current_scene)
    {
    case TITLE_SCENE:
        title_scene->draw_ui();
        break;
    case BATTLE_SCENE:
        game_scene->draw_ui();
        break;
    case SET_SCENE:
        setting_scene->draw_ui();
        break;
    }
}

// get mouse position, return hovered button index
void Scene_manager::mouse_in(int x, int y)
{
    switch (current_scene)
    {
    case TITLE_SCENE:
        mouse_on = title_scene->mouse_act(x, y);
        break;
    case SET_SCENE:
        mouse_on = setting_scene->mouse_act(x, y);
        break;
    case BATTLE_SCENE:
        mouse_on = game_scene->mouse_act(x, y);
        break;
    }
}

void Scene_manager::key_in()
{
    game_scene->keyboard_act();
}

// define the button-pressed-based change scene logic
void Scene_manager::change_scene()
{
    if (current_scene == TITLE_SCENE)
    {
        switch (mouse_on)
        {
        case START_BUTTON:
            current_scene = BATTLE_SCENE;
            break;
        case CREDIT_BUTTON:
            current_scene = CREDIT_SCENE;
            break;
        case SET_BUTTON:
            prev_scene = TITLE_SCENE; // for game scene set button: prev = game scene
            current_scene = SET_SCENE;
            break;
        }
    }
    else if (current_scene == CREDIT_SCENE)
    {
        current_scene = TITLE_SCENE;
    }
    else if (current_scene == SET_SCENE)
    {
        switch (mouse_on)
        {
        case RESUME_BUTTON:
            current_scene = prev_scene;
            break;
        case RESTART_BUTTON:
            current_scene = TITLE_SCENE;
            break;
        case EXIT_BUTTON:
            // exit_game = true;
            break;
        case AUDIO_BUTTON:
            game_mute = !game_mute;
            break;
        }
    }
    else if (current_scene == BATTLE_SCENE)
    {
        switch (mouse_on)
        {
        case PAUSE_BUTTON:
            prev_scene = BATTLE_SCENE;
            current_scene = SET_SCENE;
            break;
        }
    }
}

Scene_manager::~Scene_manager()
{
    al_destroy_bitmap(credit_scene);
    al_destroy_sample(sample);
    al_destroy_sample_instance(title_bgm);
    al_destroy_sample_instance(game_bgm);

    delete title_scene;
    delete game_scene;
    delete setting_scene;
    // delete end_scene;
}
