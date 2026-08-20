//
// Created by chris on 7/6/26.
//

#include "Asteroids_Game.h"

#include "Player.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <random>

void Asteroids_Game::init()
{
    obj_manager.create_objects_init(r_engine,log);
    aster_manager.init_package();
    score = 0;
    score_scaler = 1;
    has_beaten_highscore = false;
}

void Asteroids_Game::run_game()
{
    high_score = 0; // TEMP, ADD TO FILE???

    window.create(sf::VideoMode(WINDOW_SIZE),"Asteroids");
    window.setFramerateLimit(60);

    sf::Image da_icon;
    if ( !da_icon.loadFromFile("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/space_ship_p_v3.png"))
        std::cout << "Icon failed, rip\n";
    else
         window.setIcon(da_icon.getSize(), da_icon.getPixelsPtr());

    ImGui::SFML::Init(window);

    obj_manager.player_is_dead = true;
    float f_player_shots = 0;
    bool player_reloading_shot = false;

    obj_manager.reset_game();
    r_engine.reset_game();
    init();

    sound_track.emplace_back("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/ACTUAL_Music/track1.wav");
    sound_track.emplace_back("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/ACTUAL_Music/track2.mp3");
    sound_track.emplace_back("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/ACTUAL_Music/track3.mp3");
    sound_track.emplace_back("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/ACTUAL_Music/track4.wav");
    sound_track.emplace_back("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/ACTUAL_Music/track5.wav");
    sound_track.emplace_back("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/ACTUAL_Music/track6.wav");
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(sound_track), std::end(sound_track), rng);

    while (window.isOpen())
    {
        delta_time = clock.restart();
        delta_time_seconds = delta_time.asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backslash))
            obj_manager.player_is_dead = true;

        // ———————————————————————————————————————
        // SCORE STUFF
        // ———————————————————————————————————————
        if (obj_manager.player_is_dead == false)
        {
            if (timer_add_score < 1)
            {
                score += 10 * score_scaler;
                score_scaler += 0.5;
                timer_add_score = 60;
            }
            else timer_add_score--;

            score += obj_manager.score_personal;
            obj_manager.score_personal = 0.0f;

            if (high_score < score)
            {
                if (has_beaten_highscore == false and high_score != 0)
                    sound_beat_highscore.play();
                high_score = score;
                has_beaten_highscore = true;
            }
        }

        // ———————————————————————————————————————
        // MUSIC
        // ———————————————————————————————————————
        if (obj_manager.player_is_dead == true and
            sound_track.at(current_track_playing).getVolume() > PLAYER_DEAD_MUSIC_VOLUME)
        {
            sound_track.at(current_track_playing).setVolume(sound_track.at(current_track_playing).getVolume() - 1 );
        } else if((obj_manager.player_is_dead == false and
            sound_track.at(current_track_playing).getVolume() < MUSIC_VOLUME))
        {
            sound_track.at(current_track_playing).setVolume(sound_track.at(current_track_playing).getVolume() + 1 );
        } else if((obj_manager.player_is_dead == false and
            sound_track.at(current_track_playing).getVolume() > MUSIC_VOLUME))
        {
            sound_track.at(current_track_playing).setVolume(MUSIC_VOLUME);
        }

        if (sound_track.at(current_track_playing).getStatus() != sf::SoundSource::Status::Playing)
        {
            if ((sound_track.size() - (current_track_playing + 1) ) > 0)
                current_track_playing++;
            else
                current_track_playing = 0;

            sound_track.at(current_track_playing).setVolume(PLAYER_DEAD_MUSIC_VOLUME);
            sound_track.at(current_track_playing).play();
        }

        // ———————————————————————————————————————
        // UI
        // ———————————————————————————————————————

        ImGui::SFML::Update(window, clock.restart());

        ImGuiWindowFlags button_rest_flags =
           ImGuiWindowFlags_NoDecoration |
           ImGuiWindowFlags_NoMove |
           ImGuiWindowFlags_NoBackground |
           ImGuiWindowFlags_NoSavedSettings |
           ImGuiWindowFlags_AlwaysAutoResize;


        ImGui::SetNextWindowPos(
            ImVec2(WINDOW_SIZE.x / 2.0f, WINDOW_SIZE.y / 2.0f),
            ImGuiCond_Always,
            ImVec2(0.5f, 0.5f)
        );

        ImGui::Begin("Play Again Button", nullptr, button_rest_flags);

        if (obj_manager.player_is_dead == true)
        {
            std::string play_message;
            if (first_opened_game == true)
                 play_message = "Play";
            else
                play_message = "Play Again?";
            char const *casted_play_message = play_message.c_str();
            if (ImGui::Button(casted_play_message, ImVec2(100.0f,50.0f)))
            {
                if (play_message != "Play")
                {
                    obj_manager.reset_game();
                    r_engine.reset_game();
                    init();
                    obj_manager.player_is_dead = false;
                    first_opened_game = false;
                    sound_play_again.play();
                } else
                {
                    obj_manager.player_is_dead = false;
                    first_opened_game = false;
                    sound_play_again.play();
                }
            }
        }

        ImGui::End();

        ImGuiFocusedFlags score_flags =
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize;
        if (obj_manager.player_is_dead == false)
        {
            ImGui::SetNextWindowPos(
                        ImVec2(650,60),
                        ImGuiCond_Always,
                        ImVec2(0.5f, 0.5f)
                    );
        } else
        {
            ImGui::SetNextWindowPos(
            ImVec2(WINDOW_SIZE.x / 2.0f, (WINDOW_SIZE.y / 2.0f) - 100),
            ImGuiCond_Always,
            ImVec2(0.5f, 0.5f)
            );
        }
        ImGui::Begin("score" , nullptr, score_flags);

        if (obj_manager.player_is_dead == false)
        {
            std::string s = std::to_string(score);
            char const *casted_score = s.c_str();
            ImGui::Text(casted_score, ImVec2(50,30));
        }
        else
        {
            ImGui::Text("Final Score: \n", ImVec2(50,30));
            std::string message = std::to_string(score);

            auto windowWidth = ImGui::GetWindowSize().x;
            auto textWidth   = ImGui::CalcTextSize(message.c_str()).x;

            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

            char const *casted_score = message.c_str();

            ImGui::Text(casted_score, ImVec2(50,30));

            ImGui::Text("High_score score: \n", ImVec2(50,30));
            std::string other_message = std::to_string(high_score);

            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

            char const *casted_high_score = other_message.c_str();
            ImGui::Text(casted_high_score, ImVec2(50,30));

        }

        ImGui::End();

        ImGui::SetNextWindowPos(
            ImVec2(570,60),
            ImGuiCond_Always,
            ImVec2(0.5f, 0.5f)
        );

        ImGui::Begin("Score_label_alive", nullptr, score_flags);

        if (obj_manager.player_is_dead == false)
        {

            ImGui::Text("Score: ", ImVec2(100, 50));
        }

        ImGui::End();

        ImGui::SetNextWindowPos(
                   ImVec2(570,30),
                   ImGuiCond_Always,
                   ImVec2(0.5f, 0.5f)
               );

        ImGui::Begin("Lives text", nullptr, score_flags);

        if (obj_manager.player_is_dead == false)
        {

            ImGui::Text("Lives: ", ImVec2(100, 50));
        }

        ImGui::End();

        ImGui::SetNextWindowPos(
                  ImVec2(650,30),
                  ImGuiCond_Always,
                  ImVec2(0.5f, 0.5f)
              );

        ImGui::Begin("Lives label", nullptr, score_flags);

        if (obj_manager.player_is_dead == false)
        {

            ImGui::Text(std::to_string(obj_manager.player_lives).c_str(), ImVec2(100, 50));
        }

        ImGui::End();

        // amount of shots bar
        ImGui::SetNextWindowPos(
            ImVec2(600,90),
            ImGuiCond_Always,
            ImVec2(0.5f, 0.5f)
            );

        ImGui::Begin("Power bar", nullptr, button_rest_flags);
        if (obj_manager.player_is_dead == false)
        {
            if (obj_manager.player_shots > 1)
            {
                f_player_shots = (static_cast<float>(obj_manager.player_shots) * 0.0625);
                if (playing_reloading_sound == true)
                {
                    sound_finish_reloading.play();
                    playing_reloading_sound = false;
                }
            }
            else
            {
                if (obj_manager.player_shots > 0)
                    f_player_shots = 0;
                f_player_shots -= 0.05;
                if (sound_reload.get_status() != sf::SoundSource::Status::Playing)
                {
                    sound_reload.play();
                    playing_reloading_sound = true;
                }
            }
            ImGui::ProgressBar(f_player_shots, {100, 20} );
        }
        ImGui::End();

        // ———————————————————————————————————————
        // EVIL ASTEROID
        // ———————————————————————————————————————
        if (obj_manager.timer_evil_asteroid < 1 and obj_manager.player_is_dead == false)
        {
            aster_manager.create_evil_asteroid(obj_manager.player_position);
            obj_manager.timer_evil_asteroid = obj_manager.AMOUNT_EVIL_ASTEROID_TIMER;
        }
        if (!obj_manager.timer_evil_asteroid < 1 and obj_manager.player_is_dead == false)
            obj_manager.timer_evil_asteroid--;

        // ———————————————————————————————————————
        // END FRAME UPDATING
        // ———————————————————————————————————————

        window.clear();
        if (obj_manager.player_is_dead == false)
            update_objects();
        r_engine.draw_objects(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void Asteroids_Game::update_objects()
{
    obj_manager.update_objects(delta_time_seconds);
    aster_manager.place_asteroids();
}



