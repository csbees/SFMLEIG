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
    window.setFramerateLimit(60);
    obj_manager.create_objects_init(r_engine,log);
}

void Asteroids_Game::run_game()
{
    window.create(sf::VideoMode(WINDOW_SIZE),"Asteroids");
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

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
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



