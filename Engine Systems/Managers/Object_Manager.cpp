//
// Created by chris on 7/4/26.
//

#include "Object_Manager.h"

// Collision need to be rewritten anyway, so commented this out for now.
// I think I want this to happen in update()
// void Object_Manager::find_collision(const float d_time) const
// {
//     for (const auto e : the_entities)
//     {
//         e->node.sprite.setPosition(e->x_,e->y_);
//         e->delta_time = d_time;
//         e->update();
//     }
//
//     // O(n^2) collision — this is very slow indeed, however, for pong, it works great!
//     sf::FloatRect other_box;
//     for (const auto& i : the_entities)
//     {
//         other_box = i->node.sprite.getGlobalBounds();
//         for (const auto& j : the_entities)
//         {
//             sf::FloatRect boundingBox = j->node.sprite.getGlobalBounds();
//
//             if (boundingBox.intersects(other_box) and j->node.ID != i->node.ID)
//             {
//                 i->collided();
//             }
//         }
//     }
//
// }