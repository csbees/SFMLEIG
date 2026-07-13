//
// Created by chris on 7/6/26.
//

#include "Asteroids_Game.h"

#include "Player.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"


void Asteroids_Game::init()
{
    // ————— setup window ——————
    //window.setIcon() // TODO: Do this some time
    window.setFramerateLimit(60);
    obj_manager.create_game_objects(r_engine,log);
}

void Asteroids_Game::run_game()
{
    sf::Time delta_time = clock.restart();
    float delta_time_seconds = delta_time.asSeconds();

    window.create(sf::VideoMode(WINDOW_SIZE),"Asteroids");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        update_objects();
        r_engine.draw_objects(window);
        window.display();
    }
}

void Asteroids_Game::update_objects()
{
    obj_manager.update_objects();
    aster_manager.place_asteroids();
    aster_manager.update();
}



