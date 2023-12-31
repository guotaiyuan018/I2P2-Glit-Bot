#include "scene_manager.h"
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

Scene_manager::Scene_manager(){
    current_scene = 0;
    prev_scene = current_scene;
    title_scene = new Title_scene();
    game_scene = new Game_scene();
    setting_scene = new Setting_scene();
    //end_scene = new End_scene();
}

void Scene_manager::load_scenes(){
    al_reserve_samples(15);
    title_scene->load_scene();
    game_scene->load_scene();
    setting_scene->load_scene();
    //end_scene->load_scene();

    credit_scene = al_load_bitmap("./Scenes/credit.png");

    //audio
    sample = al_load_sample("./audio/title.wav");
    title_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(title_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(title_bgm, al_get_default_mixer());

    sample = al_load_sample("./audio/game.mp3");
    game_bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(game_bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(game_bgm, al_get_default_mixer());
}

void Scene_manager::draw_scene(int scene, int counter){
    //cout << "start to draw scene: " << scene << endl;
    switch(scene){
    case TITLE_SCENE:
        //audio
        if(al_get_sample_instance_playing(game_bgm))
            al_stop_sample_instance(game_bgm);

        if(!game_mute)al_play_sample_instance(title_bgm);
        else al_stop_sample_instance(title_bgm);
        //visual
        title_scene->draw_scene(counter);
        break;

    case BATTLE_SCENE:
        //audio
        if(al_get_sample_instance_playing(title_bgm))
            al_stop_sample_instance(title_bgm);

        if(!game_mute)al_play_sample_instance(game_bgm);
        else al_stop_sample_instance(game_bgm);

        //visual
        game_scene->draw_scene();
        break;

    case SET_SCENE:
        //audio
        if(game_mute){
            al_set_sample_instance_gain(title_bgm, 0);
            al_set_sample_instance_gain(game_bgm, 0);
        }
        else {
            switch(prev_scene){
            case TITLE_SCENE:
                al_set_sample_instance_gain(title_bgm, 1);
                break;
            case BATTLE_SCENE:
                al_set_sample_instance_gain(game_bgm, 1);
                break;
            }
        }
        //visual
        setting_scene->draw_scene();
        break;

    case CREDIT_SCENE:
        al_draw_bitmap(credit_scene, 0, 0, 0);
        break;
    }
    //cout << "draw scene finish\n";
}

void Scene_manager::change_scene(int change){
    current_scene = change;
}

//get mouse position, return hovered button index
void Scene_manager::mouse_in(int x, int y){
    switch(current_scene){
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

//define the button-pressed-based change scene logic
int Scene_manager::get_change(){
    if(current_scene == TITLE_SCENE){
        switch(mouse_on){
        case START_BUTTON:
            return BATTLE_SCENE;
        case CREDIT_BUTTON:
            return CREDIT_SCENE;
        case SET_BUTTON:
            prev_scene = TITLE_SCENE;//for game scene set button: prev = game scene
            return SET_SCENE;
        default:
            return current_scene;
        }
    }
    else if(current_scene == CREDIT_SCENE){
        return TITLE_SCENE;
    }
    else if(current_scene == SET_SCENE){
        switch(mouse_on){
        case RESUME_BUTTON:
            return prev_scene;
        case RESTART_BUTTON:
            return BATTLE_SCENE;
        case EXIT_BUTTON:
            return TITLE_SCENE;
        case AUDIO_BUTTON:
            game_mute = !game_mute;
            return current_scene;
        }
    }
    else if(current_scene == BATTLE_SCENE){
        switch(mouse_on){
        case PAUSE_BUTTON:
            prev_scene = BATTLE_SCENE;
            return SET_SCENE;
        }
    }
    return current_scene;
}

Scene_manager::~Scene_manager(){
    al_destroy_bitmap(credit_scene);
    al_destroy_sample(sample);
    al_destroy_sample_instance(title_bgm);
    al_destroy_sample_instance(game_bgm);

    delete title_scene;
    delete game_scene;
    delete setting_scene;
    //delete end_scene;
}
