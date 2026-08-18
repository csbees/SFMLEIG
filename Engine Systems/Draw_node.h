//
// Created by chris on 6/24/26.
//


#pragma once

#include "node_hitbox.h"
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
    Draw_node() : sprite(texture), node_hitbox(sprite) {}

    bool flag_is_animated  = false;
    bool flag_render_self  = true;
    bool flag_dead         = false;
    bool flag_using_hitbox = false;

    sf::Vector2f origin = {0,0};
    sf::Vector2f scale = {1,1};

    Node_Hitbox node_hitbox;

    OBJECT_TYPE my_type = UNKNOWN;
};

