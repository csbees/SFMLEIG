//
// Created by chris on 7/6/26.
//

#pragma once


#include "../Engine Systems/logger.h"
#include "../Engine Systems/Render_engine.h"
#include "../Engine Systems/Managers/Game.h"
#include "../Engine Systems/Managers/Object_Manager.h"

class Asteroids_Game final : public Game
{
public:
    // Sets up essential systems
    void init() override;
    // Runs every frame,
    void run_game() override;
    void update_objects() const;

private:
    logger log;
    Render_engine r_engine;
    sf::RenderWindow window;
    Object_Manager obj_manager;

    const sf::Vector2u WINDOW_SIZE = sf::Vector2<int unsigned>(700,700);


};

