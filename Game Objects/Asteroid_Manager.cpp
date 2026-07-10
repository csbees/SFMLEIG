//
// Created by chris on 7/10/26.
//

#include "Asteroid_Manager.h"

void Asteroid_Manager::create_asteroid(Physics_node node_phy)
{
    auto asteroid = std::make_unique<Asteroid>(r_engine, log, node_phy ,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
    all_asteroids.push_back(std::move(asteroid));
}

// A note on this function: I could make a system that can adjust to different screen sizes dynamically, but,
// that would take time, and I just don't care that much. So hard coded it is.
Physics_node Asteroid_Manager::prep_new_asteroid_phy_node()
{

}

