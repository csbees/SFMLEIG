//
// Created by chris on 7/10/26.
//

#include "Asteroid_Manager.h"

void Asteroid_Manager::create_asteroid(const Physics_node& node_phy)
{
    obj_manager.create_object<Asteroid>(r_engine, log, node_phy ,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
}

// TODO: figure out a better way to get random numbers
// also maybe remove some of these magic numbers.
void Asteroid_Manager::place_asteroids()
{
    // TODO: Maybe add delta time here?
    if (create_asteroid_timer > 1) { create_asteroid_timer--; return;}
    Physics_node asteroid_phy_node;

    int which_side = rand() % 4;
    // int which_side = 0;
    if (which_side == 0)
    {
        asteroid_phy_node.position.y = -100;
        asteroid_phy_node.position.x = rand() % 500;
        asteroid_phy_node.angle_degrees = (rand() % 90) + 60;
        asteroid_phy_node.general_velocity = 0.1;

    } else if (which_side == 1)
    {
        asteroid_phy_node.position.y = 700;
        asteroid_phy_node.position.x = rand() % 500;
        asteroid_phy_node.angle_degrees = (rand() % 90) - 110;
        asteroid_phy_node.general_velocity = 0.1;
    }
    if (which_side == 2)
    {
        asteroid_phy_node.position.y = rand() % 500;
        asteroid_phy_node.position.x = -100;
        asteroid_phy_node.angle_degrees = (rand() % 90) - 45;
        asteroid_phy_node.general_velocity = 0.1;

    } else if (which_side == 3)
    {
        asteroid_phy_node.position.y = rand() % 500;
        asteroid_phy_node.position.x = 700;
        asteroid_phy_node.angle_degrees = (rand() % 90) + 110;
        asteroid_phy_node.general_velocity = 0.1;
    }
    create_asteroid(asteroid_phy_node);
    create_asteroid_timer = 2000;
}
