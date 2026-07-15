//
// Created by chris on 7/6/26.
//

#pragma once


#include "Asteroid_Manager.h"
#include "../Engine Systems/logger.h"
#include "../Engine Systems/Render_engine.h"
#include "../Engine Systems/Managers/Game.h"
#include "../Engine Systems/Managers/Object_Manager.h"

class Asteroids_Game final : public Game
{
public:
    Asteroids_Game() : aster_manager(r_engine,log) {}
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


};

