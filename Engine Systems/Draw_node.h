//
// Created by chris on 6/24/26.
//


#pragma once

#include "SFML/Graphics/Sprite.hpp"

// I mean, this isn't really scalable, but bruh do you think I care
// Maybe something like typeid(*i).name() or dynamic_cast would work
enum OBJECT_TYPE
{
    PLAYER,
    ASTEROID,
    BULLET,
    UNKNOWN
};

struct Draw_node
{
    unsigned int ID = 0;
    sf::Texture texture;
    sf::Sprite sprite;
    Draw_node() : sprite(texture) {}

    bool flag_is_animated = false;
    bool flag_render_self = true;
    bool flag_dead        = false;

    OBJECT_TYPE my_type = UNKNOWN;
};

