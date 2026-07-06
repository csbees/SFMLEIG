//
// Created by chris on 6/24/26.
//


#pragma once

#include "SFML/Graphics/Sprite.hpp"

struct Draw_node
{
    unsigned int ID = 0;
    bool is_animated = false;
    sf::Texture texture;
    sf::Sprite sprite;
    Draw_node() : sprite(texture) {}
};

