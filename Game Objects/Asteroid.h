//
// Created by chris on 7/6/26.
//

#pragma once
#include "../Engine Systems/Entity.h"



class Asteroid : public Entity
{
public:
    Asteroid(Render_engine& given_r_engine,
           logger& given_log,
           const Physics_node& asteroid_phy_node,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file)
    {
        node_phy.position.x = asteroid_phy_node.position.x;
        node_phy.position.y = asteroid_phy_node.position.y;
        node_phy.angle_degrees = asteroid_phy_node.angle_degrees;
        node_phy.general_velocity = asteroid_phy_node.general_velocity;

        node_draw.my_type = ASTEROID;
    }

    void update(float) override;
    void collided() override;
};
