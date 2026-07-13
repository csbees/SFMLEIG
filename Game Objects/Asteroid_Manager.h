//
// Created by chris on 7/10/26.
//

#pragma once
#include <vector>

#include "Asteroid.h"
#include "../Engine Systems/Physics_node.h"


class Asteroid_Manager
{
public:
    explicit Asteroid_Manager(Render_engine& given_r_engine, logger& given_log) : r_engine(given_r_engine), log(given_log) {}

    // Runs every frame; calls for asteroids to be created and gives a location
    void place_asteroids();
    void update();
private:
    void create_asteroid(Physics_node node_phy);
    Render_engine& r_engine;
    logger& log;
    int create_asteroid_timer = 0;

    std::vector<std::unique_ptr<Asteroid>> all_asteroids;
};



