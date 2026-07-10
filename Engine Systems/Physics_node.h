//
// Created by chris on 7/10/26.
//

#pragma once

#include <SFML/Graphics.hpp>

struct Physics_node
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float general_velocity = 0;
    float angle_degrees = 0;
    float angle_radians = 0;
};
