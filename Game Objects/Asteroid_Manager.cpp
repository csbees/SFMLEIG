//
// Created by chris on 7/10/26.
//

#include "Asteroid_Manager.h"

void Asteroid_Manager::create_asteroid(Physics_node node_phy)
{
    auto asteroid = std::make_unique<Asteroid>(r_engine, log, node_phy ,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
    all_asteroids.push_back(std::move(asteroid));
}

void Asteroid_Manager::update()
{
    for (auto& i : all_asteroids)
    {
        i->update();
    }
}


void Asteroid_Manager::place_asteroids()
{
    if (create_asteroid_timer > 1) { create_asteroid_timer--; return;}
    Physics_node asteroid_phy_node;

    int which_side = rand() % 4;
    // int which_side = 0;
    if (which_side == 0)
    {
        asteroid_phy_node.position.y = -100;
        asteroid_phy_node.position.x = rand() % 500;
        asteroid_phy_node.angle_degrees = (rand() % 90) + 60;
        asteroid_phy_node.general_velocity = 4;

    } else if (which_side == 1)
    {
        asteroid_phy_node.position.y = 700;
        asteroid_phy_node.position.x = rand() % 500;
        asteroid_phy_node.angle_degrees = (rand() % 90) - 110;
        asteroid_phy_node.general_velocity = 4;
    }
    if (which_side == 2)
    {
        asteroid_phy_node.position.y = rand() % 500;
        asteroid_phy_node.position.x = -100;
        asteroid_phy_node.angle_degrees = (rand() % 90) - 45;
        asteroid_phy_node.general_velocity = 4;

    } else if (which_side == 3)
    {
        asteroid_phy_node.position.y = rand() % 500;
        asteroid_phy_node.position.x = 700;
        asteroid_phy_node.angle_degrees = (rand() % 90) + 110;
        asteroid_phy_node.general_velocity = 4;
    }
    std::cout << "xy: " << asteroid_phy_node.position.x << '\n' << asteroid_phy_node.position.y << '\n'
            << "deg: " <<asteroid_phy_node.angle_degrees << "\n\n";
    create_asteroid(asteroid_phy_node);
    create_asteroid_timer = 100;
}
