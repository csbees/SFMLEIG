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
}

void Asteroids_Game::run_game()
{
    window.create(sf::VideoMode(WINDOW_SIZE),"Asteroids");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

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
            if (ImGui::Button("Play Again?", ImVec2(100.0f,50.0f)))
            {
                obj_manager.reset_game();
                r_engine.reset_game();
                init();
                obj_manager.player_is_dead = false;
            }
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



