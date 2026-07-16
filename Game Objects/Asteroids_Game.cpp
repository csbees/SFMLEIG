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
    obj_manager.create_objects_init(r_engine,log);
}

void Asteroids_Game::run_game()
{
    window.create(sf::VideoMode(WINDOW_SIZE),"Asteroids");
    while (window.isOpen())
    {
        delta_time = clock.restart();
        delta_time_seconds = delta_time.asSeconds();

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
    obj_manager.update_objects(delta_time_seconds);
    aster_manager.place_asteroids();
}



