//
// Created by chris on 7/10/26.
//

#pragma once
#include <vector>

#include "Asteroid.h"
#include "../Engine Systems/Physics_node.h"
#include "../Engine Systems/Managers/Object_Manager.h"


class Asteroid_Manager
{
public:
    Asteroid_Manager(Render_engine& given_r_engine, logger& given_log, Object_Manager& given_object_manager)
        : r_engine(given_r_engine), log(given_log), obj_manager(given_object_manager) {}

    // Runs every frame; calls for asteroids to be created and gives a location
    void place_asteroids();
    std::vector<std::unique_ptr<Asteroid>> all_asteroids;
private:
    void create_asteroid(const Physics_node& node_phy);

    Render_engine& r_engine;
    logger& log;
    Object_Manager& obj_manager;
    int create_asteroid_timer = 0;



};



