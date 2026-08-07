//
// Created by chris on 7/10/26.
//

#include "Asteroid_Manager.h"
#include <random>

void Asteroid_Manager::place_asteroids()
{
    // TODO: Maybe add delta time here
    if (create_asteroid_timer > 1) { create_asteroid_timer--; return;}
    Physics_node asteroid_phy_node;

    std::mt19937 rng(std::random_device{}());

    auto which_side = std::uniform_int_distribution<int>(1, 4)(rng);
    auto pos_r =  std::uniform_real_distribution<float>(0, 500)(rng);
    auto degrees_r = std::uniform_real_distribution<float>(0, 90)(rng);

    asteroid_phy_node.general_velocity =  std::uniform_real_distribution<float>(40, 200)(rng);

    // TODO: When I add different resolutions, fix this
    if (which_side == 1)
    {
        asteroid_phy_node.position.y = -100;

        asteroid_phy_node.position.x = pos_r;
        asteroid_phy_node.angle_degrees = degrees_r + 60;

    } else if (which_side == 2)
    {
        asteroid_phy_node.position.y = 700;
        asteroid_phy_node.position.x = pos_r;
        asteroid_phy_node.angle_degrees = degrees_r - 110;
    }
    if (which_side == 3)
    {
        asteroid_phy_node.position.y = pos_r;
        asteroid_phy_node.position.x = -100;
        asteroid_phy_node.angle_degrees = degrees_r - 45;

    } else if (which_side == 4)
    {
        asteroid_phy_node.position.y = pos_r;
        asteroid_phy_node.position.x = 700;
        asteroid_phy_node.angle_degrees = degrees_r + 110;
    }
    create_asteroid(asteroid_phy_node);
    create_asteroid_timer = 2000;
}
