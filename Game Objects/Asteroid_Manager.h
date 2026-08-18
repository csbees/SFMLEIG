//
// Created by chris on 7/10/26.
//

#pragma once
#include <vector>

#include "../Engine Systems/Physics_node.h"
#include "../Engine Systems/logger.h"
#include "../Engine Systems/Render_engine.h"
#include "../Engine Systems/Managers/Object_Manager.h"

#include "Asteroid.h"

//class Object_Manager;

class Asteroid_Manager
{
public:
    Asteroid_Manager(Render_engine& given_r_engine, logger& given_log, Object_Manager& given_object_manager)
        : r_engine(given_r_engine), log(given_log), obj_manager(given_object_manager) {}

    // Runs every frame; calls for asteroids to be created and gives a location
    void place_asteroids();
    void create_asteroid(const Physics_node& node_phy);
    std::vector<std::unique_ptr<Asteroid>> all_asteroids;
private:
    void create_asteroid_medium(const Physics_node& node_phy);
    void create_asteroid_small (const Physics_node& node_phy);


    Render_engine& r_engine;
    logger& log;
    Object_Manager& obj_manager;
    int create_asteroid_timer = 0;

    float CREATE_ASTER_TIME = 100;
};

inline void Asteroid_Manager::create_asteroid(const Physics_node& node_phy)
{
    obj_manager.create_object<Asteroid>(r_engine, log, node_phy ,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/rock_p.png",
       this, 1);
}


