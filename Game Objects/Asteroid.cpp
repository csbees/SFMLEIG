//
// Created by chris on 7/6/26.
//

#include "Asteroid.h"

void Asteroid::collided()
{
    node_draw.flag_dead = true;
    label_dead = true;
    // TODO: Make it so asteroids make more asteroids when it
}

void Asteroid::update(float delta_time)
{
    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);

    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;

    node_draw.sprite.setRotation(sf::degrees(node_phy.angle_degrees));
    node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));
}

