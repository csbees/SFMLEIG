//
// Created by chris on 7/6/26.
//

#pragma once


#include "Asteroid_Manager.h"
#include "../Engine Systems/logger.h"
#include "../Engine Systems/Render_engine.h"
#include "../Engine Systems/sound_container.h"
#include "../Engine Systems/Managers/Game.h"
#include "../Engine Systems/Managers/Object_Manager.h"
#include "SFML/Audio/Music.hpp"

class Asteroids_Game final : public Game
{
public:
    Asteroids_Game()
        : obj_manager(r_engine), aster_manager(r_engine,log, obj_manager),
          sound_play_again("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/start_game.wav"),
          sound_beat_highscore("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/beat_highscore.mp3"),
          sound_engine("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/UGG.mp3"),
          sound_finish_reloading("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/finish_reload.mp3"),
          sound_reload("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/reload_sound_again.wav")
    {}
    // Sets up essential systems
    void init() override;
    // Runs every frame,
    void run_game() override;
    void update_objects();
private:
    logger log;
    Render_engine r_engine;
    sf::RenderWindow window;
    Object_Manager obj_manager;
    Asteroid_Manager aster_manager;
    sf::Clock clock;

    const sf::Vector2u WINDOW_SIZE = sf::Vector2<int unsigned>(700,700);

    sf::Time delta_time = clock.restart();
    float delta_time_seconds = delta_time.asSeconds();

    int score = 0;
    // I would like to have this stored and loaded in a file. TODO: Look at king me and remember how
    // I set it to 0 in at the beginning of run_game( right now
    int high_score;
    float score_scaler = 1;
    int timer_add_score = 60;
    bool has_beaten_highscore = false;

    bool space_pressed = false;

    bool first_opened_game = true;

    std::vector<sf::Music> sound_track;

    Sound_Container sound_play_again;
    Sound_Container sound_beat_highscore;
    Sound_Container sound_reload;
    Sound_Container sound_finish_reloading;

    Sound_Container sound_engine;

     Draw_node background;

    bool playing_reloading_sound = false;

    // the index for sound_track
    int current_track_playing = 0;
    const float PLAYER_DEAD_MUSIC_VOLUME = 30;
    const float MUSIC_VOLUME = 100;



};

