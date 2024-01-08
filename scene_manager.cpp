#include "scene_manager.h"
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

Scene_manager::Scene_manager()
{
    cur_scene = 0;
    prev_scene = cur_scene;
    title_scene = new Title_scene();
    game_scene = new Game_scene();
    setting_scene = new Setting_scene();
    end_scene = new End_scene();
}

void Scene_manager::load_scenes()
{
    al_reserve_samples(15);

    title_scene->load_scene();

    al_draw_bitmap(load_page[1], 0, 0, 0);
    al_flip_display();

    game_scene->load_scene();

    al_draw_bitmap(load_page[2], 0, 0, 0);
    al_flip_display();

    setting_scene->load_scene();
    end_scene->load_scene();

    char buffer[50];

    for(int i = 0; i < credit_frames; i++)
    {
        sprintf(buffer, "./Scenes/credit/breakdown/img%d.png", i+1);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        if(img) credit_background.push_back(img);
    }
    credit_text = al_load_bitmap("./Scenes/credit/text.png");

    //audio
    sample = al_load_sample("./audio/title.wav");
    title_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(title_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(title_bgm, al_get_default_mixer());

    sample = al_load_sample("./audio/game.mp3");
    game_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(game_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(game_bgm, al_get_default_mixer());

    sample = al_load_sample("./audio/bonefire.wav");
    fire_sfx = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(fire_sfx, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(fire_sfx, al_get_default_mixer());

    sample = al_load_sample("./audio/bonus.wav");
    bonus_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(bonus_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bonus_bgm, al_get_default_mixer());

    sample = al_load_sample("./audio/boss.wav");
    boss_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(boss_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(boss_bgm, al_get_default_mixer());
}

void Scene_manager::draw_background(int anime_counter)
{
    switch(cur_scene)
    {
        case TITLE_SCENE:
            //audio
            if(al_get_sample_instance_playing(game_bgm))
                al_stop_sample_instance(game_bgm);

            if(al_get_sample_instance_playing(bonus_bgm))
                al_stop_sample_instance(bonus_bgm);

            if(al_get_sample_instance_playing(fire_sfx))
                al_stop_sample_instance(fire_sfx);

            if(al_get_sample_instance_playing(boss_bgm))
                al_stop_sample_instance(boss_bgm);

            if(!game_mute)
            {
                al_set_sample_instance_gain(title_bgm, 1);
                al_play_sample_instance(title_bgm);
            }
            else al_stop_sample_instance(title_bgm);

            //visual
            title_scene->draw_background(anime_counter % title_frames);
            break;

        case BATTLE_SCENE:
            //audio
            if(al_get_sample_instance_playing(title_bgm))
                al_stop_sample_instance(title_bgm);

            if(!game_mute)
            {
                switch(cur_stage)
                {
                case 2: // bonus
                {
                    if(al_get_sample_instance_playing(game_bgm))
                        al_stop_sample_instance(game_bgm);

                    al_set_sample_instance_gain(fire_sfx, healing ? 0.5 : 0.1);
                    al_set_sample_instance_gain(bonus_bgm, 1);
                    al_play_sample_instance(fire_sfx);
                    al_play_sample_instance(bonus_bgm);

                    break;
                }
                case 3: // boss
                {
                    if(al_get_sample_instance_playing(bonus_bgm))
                        al_stop_sample_instance(bonus_bgm);

                    if(al_get_sample_instance_playing(fire_sfx))
                        al_stop_sample_instance(fire_sfx);

                    al_set_sample_instance_gain(boss_bgm, 1);
                    al_play_sample_instance(boss_bgm);

                    if(stage_clear)
                    {
                        if(al_get_sample_instance_playing(boss_bgm))
                            al_stop_sample_instance(boss_bgm);
                        al_play_sample_instance(game_bgm);
                    }

                    break;
                }
                default:
                {
                    al_set_sample_instance_gain(game_bgm, 1);
                    al_play_sample_instance(game_bgm);
                    break;
                }
                }
            }
            else
            {
                al_stop_sample_instance(game_bgm);
                switch(cur_stage)
                {
                case 2:
                    al_stop_sample_instance(fire_sfx);
                    al_stop_sample_instance(bonus_bgm);
                    break;
                case 3:
                    al_stop_sample_instance(boss_bgm);
                    break;
                default:
                    al_stop_sample_instance(game_bgm);
                    break;
                }
            }

            //visual
            game_scene->draw_background((anime_counter/5) % bonus_frames);
            break;

        case SET_SCENE:
            //audio
            if(game_mute)
            {
                al_set_sample_instance_gain(title_bgm, 0);
                al_set_sample_instance_gain(game_bgm, 0);
                al_set_sample_instance_gain(fire_sfx, 0);
                al_set_sample_instance_gain(bonus_bgm, 0);
                al_set_sample_instance_gain(boss_bgm, 0);
            }
            else {
                switch(prev_scene)
                {
                    case TITLE_SCENE:
                        al_set_sample_instance_gain(title_bgm, 1);
                        break;
                    case BATTLE_SCENE:
                        switch(cur_stage)
                        {
                        case 2:
                            al_set_sample_instance_gain(fire_sfx, healing ? 0.5 : 0.1);
                            al_set_sample_instance_gain(bonus_bgm, 1);
                            break;
                        case 3:
                            al_set_sample_instance_gain(boss_bgm, 1);
                            break;
                        default:
                            al_set_sample_instance_gain(game_bgm, 1);
                            break;
                        }
                }
            }

            //visual
            setting_scene->draw_background();
            break;

        case END_SCENE:
            end_scene->draw_background();
            break;

        case CREDIT_SCENE:
            al_draw_bitmap(credit_background[(anime_counter/5) % credit_frames], 0, 0, 0);
            al_draw_bitmap(credit_text, 0, 0, 0);
            break;
    }
    //cout << "sc man, draw bg finish\n";
}

void Scene_manager::draw_ui(){
    switch(cur_scene)
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
        case END_SCENE:
            end_scene->draw_ui();
            break;
    }
    //cout << "sc_man, draw ui finish\n";
}

//get mouse position, return hovered button index
void Scene_manager::mouse_in(int x, int y)
{
    switch(cur_scene)
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
        case END_SCENE:
            mouse_on = end_scene->mouse_act(x, y);
            break;
        }
}

void Scene_manager::key_in()
{
    game_scene->keyboard_act();
}

//define the button-pressed-based change scene logic
void Scene_manager::change_scene()
{
    if(cur_scene == TITLE_SCENE)
    {
        switch(mouse_on)
        {
            case START_BUTTON:
                cur_scene = BATTLE_SCENE;
                break;
            case CREDIT_BUTTON:
                cur_scene = CREDIT_SCENE;
                break;
            case SET_BUTTON:
                prev_scene = TITLE_SCENE;//for game scene set button: prev = game scene
                cur_scene = SET_SCENE;
                break;
        }
    }
    else if(cur_scene == CREDIT_SCENE)
    {
        cur_scene = TITLE_SCENE;
    }
    else if(cur_scene == SET_SCENE){
        switch(mouse_on)
        {
            case RESUME_BUTTON:
                cur_scene = prev_scene;
                break;
            case RESTART_BUTTON:
                cur_scene = TITLE_SCENE;
                reset_game = true;
                break;
            case EXIT_BUTTON:
                game_mute = true;
                exit_game = true;
                break;
            case AUDIO_BUTTON:
                game_mute = !game_mute;
                break;
        }
    }
    else if(cur_scene == BATTLE_SCENE)
    {
        if(game_won)
        {
            cur_scene = END_SCENE;
        }
        else
        {
            switch(mouse_on)
            {
                case PAUSE_BUTTON:
                    prev_scene = BATTLE_SCENE;
                    cur_scene = SET_SCENE;
                    break;
            }
        }
    }
    else if(cur_scene == END_SCENE)
    {
        switch(mouse_on)
        {
        case NEW_BUTTON:
            cur_scene = TITLE_SCENE;
            reset_game = true;
            break;
        case END_CRE_BUTTON:
            cur_scene = CREDIT_SCENE;
            break;
        case EXIT_BUTTON:
            game_mute = true;
            exit_game = true;
            break;
        }
    }
}

void Scene_manager::reset(){
    al_stop_sample_instance(title_bgm);
    al_stop_sample_instance(game_bgm);
}

Scene_manager::~Scene_manager(){
    al_destroy_sample(sample);
    al_destroy_sample_instance(title_bgm);
    al_destroy_sample_instance(game_bgm);

    for(int i = 0; i < credit_frames; i++){
        al_destroy_bitmap(credit_background[i]);
    }
    al_destroy_bitmap(credit_text);

    delete title_scene;
    delete game_scene;
    delete setting_scene;
    delete end_scene;
}
