//
// Created by chris on 7/6/26.
//

#pragma once
#include "../Engine Systems/Entity.h"

class Asteroid_Manager;

class Asteroid : public Entity
{
public:
    Asteroid(Render_engine& given_r_engine,
           logger& given_log,
           const Physics_node& asteroid_phy_node,
           const std::string& sprite_file = "-1",
           Asteroid_Manager* given_asteroid_manager = nullptr,
           int given_asteroid_type = 1,
           float given_scale_facter = 0.1)
        : Entity(given_r_engine, given_log, sprite_file)
    {
    asteroid_manager_ = given_asteroid_manager;

        node_phy.position = asteroid_phy_node.position;
        node_phy.angle_degrees = asteroid_phy_node.angle_degrees;
        node_phy.general_velocity = 5;//asteroid_phy_node.general_velocity;
        node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));

        node_draw.origin = {300,300};
        node_draw.scale = {0.1,0.1};
        sf::Vector2f hitbox_transformation = {300,300};

        node_draw.node_hitbox.set_transformations(hitbox_transformation);
        node_draw.node_hitbox.set_size(node_draw.sprite);
        node_draw.node_hitbox.set_scale(node_draw.scale);
        node_draw.node_hitbox.set_origin({node_draw.node_hitbox.get_origin().x + 60, node_draw.node_hitbox.get_origin().y});


        node_draw.my_type = ASTEROID;
        node_draw.sprite.setScale({given_scale_facter,given_scale_facter});
        node_draw.sprite.setOrigin(node_draw.origin);

        asteroid_type = given_asteroid_type;

    }

    void update(float) override;
private:
    int asteroid_type; // 1 - big, 2 - medium , 3 - small
    Asteroid_Manager* asteroid_manager_;
    int health;
    void collided() override;
};
