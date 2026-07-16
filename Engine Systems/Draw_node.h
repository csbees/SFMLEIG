//
// Created by chris on 6/24/26.
//


#pragma once

#include "SFML/Graphics/Sprite.hpp"

struct Draw_node
{
    unsigned int ID = 0;
    sf::Texture texture;
    sf::Sprite sprite;
    Draw_node() : sprite(texture) {}

    bool flag_is_animated = false;
    bool flag_render_self = true;
    bool flag_dead        = false;

    std::string my_name = "unknown";
};

