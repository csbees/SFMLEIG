//
// Created by chris on 6/24/26.
//

#ifndef DRAW_NODE_H
#define DRAW_NODE_H
#include "SFML/Graphics/Sprite.hpp"

struct Draw_node
{
    // NOTE: If a ludicrous amount of objects are added to on scene, then objects will start colliding with themselves.
    unsigned int ID = 0;

    bool is_animated = false;
    sf::Sprite sprite;
};

#endif //DRAW_NODE_H
