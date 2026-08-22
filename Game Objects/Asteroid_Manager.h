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

class Asteroid_Manager
{
public:
    Asteroid_Manager(Render_engine& given_r_engine, logger& given_log, Object_Manager& given_object_manager)
        : r_engine(given_r_engine), log(given_log), obj_manager(given_object_manager) {}

    // Runs every frame; calls for asteroids to be created and gives a location
    void place_asteroids();
    void create_asteroid(const Physics_node& node_phy);
    void init_package();
    void create_evil_asteroid(sf::Vector2f player_position);
    std::vector<std::unique_ptr<Asteroid>> all_asteroids;
private:
    void create_asteroid_medium(const Physics_node& node_phy);
    void create_asteroid_small (const Physics_node& node_phy);


    Render_engine& r_engine;
    logger& log;
    Object_Manager& obj_manager;
    int create_asteroid_timer = 0;
    bool game_just_started = true;

    sf::Vector2f speed_range = {100, 300};
    float asteroid_creation_scale = 0.1;
    float CREATE_ASTER_TIME = 100;
};

inline void Asteroid_Manager::create_asteroid(const Physics_node& node_phy)
{
    obj_manager.create_object<Asteroid>(r_engine, log, node_phy ,RESOURCES_PATH + std::string("/Art/rock_p.png"),
       this, 1, asteroid_creation_scale);
}


