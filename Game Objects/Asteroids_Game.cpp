//
// Created by chris on 7/6/26.
//

#include "Asteroids_Game.h"

#include "Player.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

void Asteroids_Game::init()
{
    // ————— setup window ——————
    //window.setIcon() // TODO: Do this some time
    obj_manager.create_objects_init(r_engine,log);
    score = 0;
    score_scaler = 1;
}

void Asteroids_Game::run_game()
{
    high_score = 0; // TEMP

    window.create(sf::VideoMode(WINDOW_SIZE),"Asteroids");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    obj_manager.player_is_dead = true;

    obj_manager.reset_game();
    r_engine.reset_game();
    init();

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

            score += r_engine.score_personal;
            r_engine.score_personal = 0.0f;

            if (high_score < score) high_score = score;
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

        ImGui::Begin("-", nullptr, button_rest_flags);

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
                obj_manager.reset_game();
                r_engine.reset_game();
                init();
                obj_manager.player_is_dead = false;
                first_opened_game = false;
                sound_play_again.play();
            }
        }

        ImGui::End();

        ImGuiFocusedFlags score_flags =
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
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



