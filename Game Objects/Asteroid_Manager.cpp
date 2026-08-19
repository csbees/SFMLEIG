//
// Created by chris on 7/10/26.
//

#include "Asteroid_Manager.h"
#include <random>

void Asteroid_Manager::place_asteroids()
{
    if (game_just_started == true)
    {
        game_just_started = false;
        for (int i = 0; i < 10; i++) place_asteroids();
    }
    // TODO: Maybe add delta time here
    if (create_asteroid_timer > 1) { create_asteroid_timer--; return;}
    Physics_node asteroid_phy_node;

    std::mt19937 rng(std::random_device{}());

    auto which_side = std::uniform_int_distribution<int>(1, 4)(rng);
    auto pos_r =  std::uniform_real_distribution<float>(0, 500)(rng);
    // auto degrees_r = std::uniform_real_distribution<float>(0, 90)(rng);

    asteroid_phy_node.general_velocity =  std::uniform_real_distribution<float>(speed_range.x, speed_range.y)(rng);

    if (which_side == 1) // top
    {
        asteroid_phy_node.position.y = -100;
        asteroid_phy_node.position.x = pos_r;
        asteroid_phy_node.angle_degrees = 90;
    } else if (which_side == 2) // bottom
    {
        asteroid_phy_node.position.y = 800;
        asteroid_phy_node.position.x = pos_r;
        asteroid_phy_node.angle_degrees = -90;

    }
    if (which_side == 3) // left
    {
        asteroid_phy_node.position.y = pos_r;
        asteroid_phy_node.position.x = -100;
        asteroid_phy_node.angle_degrees = 0;
    } else if (which_side == 4) // right
    {
        asteroid_phy_node.position.y = pos_r;
        asteroid_phy_node.position.x = 800;
        asteroid_phy_node.angle_degrees = 180;
    }
    create_asteroid(asteroid_phy_node);
    speed_range.x += 1; speed_range.y += 1;
    asteroid_creation_scale += 0.005;
    CREATE_ASTER_TIME -= 0.5;
    create_asteroid_timer = CREATE_ASTER_TIME;
}

void Asteroid_Manager::init_package()
{
    create_asteroid_timer   = 0;
    game_just_started       = true;
    asteroid_creation_scale = 0.1;
    CREATE_ASTER_TIME       = 60;
    speed_range          = {100, 300};
}
