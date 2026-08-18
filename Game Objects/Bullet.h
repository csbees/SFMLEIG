//
// Created by chris on 7/6/26.
//
#pragma once

#include "../Engine Systems/Entity.h"

class Bullet final : public Entity
{
public:
    void update(float) override;
    void collided() override;

    Bullet(Render_engine& given_r_engine,
           logger& given_log,
           const Physics_node& players_phy_node,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file)
    {
        node_phy.position.x = players_phy_node.position.x;
        node_phy.position.y = players_phy_node.position.y;
        node_phy.angle_radians = players_phy_node.angle_radians;
        node_phy.angle_degrees = players_phy_node.angle_degrees;

        node_phy.general_velocity = BULLET_SPEED + players_phy_node.general_velocity;

        node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));
        node_draw.sprite.setRotation(sf::radians(node_phy.angle_radians - 1.570796));
        node_draw.sprite.setScale({0.5,0.5});
        node_draw.sprite.setOrigin({50,25});

        node_draw.my_type = BULLET;

        disable_screen_wrap = true; // maybe? though I may want to turn it back on
    }

private:
    const float BULLET_SPEED = 1000;
};