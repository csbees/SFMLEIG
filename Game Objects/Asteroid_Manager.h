//
// Created by chris on 7/10/26.
//

#pragma once
#include <vector>

#include "Asteroid.h"
#include "../Engine Systems/Physics_node.h"


class Asteroid_Manager
{
    explicit Asteroid_Manager(Render_engine& given_r_engine) : r_engine(given_r_engine) {}


    void create_asteroid(Physics_node node_phy);
    Physics_node prep_new_asteroid_phy_node();

    Render_engine& r_engine;

    std::vector<std::unique_ptr<Asteroid>> all_asteroids;
};



