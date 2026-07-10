//
// Created by chris on 7/4/26.
//

#include "Object_Manager.h"

#include "../../Game Objects/Player.h"


void Object_Manager::update_objects() const
{
    for (auto& e : the_entities)
    {
        e->node_draw.sprite.setRotation(sf::degrees(e->node_phy.angle_degrees));
        e->node_draw.sprite.setPosition(sf::Vector2f(e->node_phy.position));
        e->update();
    }
}


void Object_Manager::create_game_objects(Render_engine& r_engine, logger& log)
{
    auto player = std::make_unique<Player>(r_engine, log,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
    // TODO: add this to the Entity constructor
    the_entities.push_back(std::move(player));
}




// Collision need to be rewritten anyway, so commented this out for now.
// I think I want this to happen in update()
// void Object_Manager::find_collision(const float d_time) const
// {
//     for (const auto e : the_entities)
//     {
//         e->node_draw_draw.sprite.setPosition(e->x_,e->y_);
//         e->delta_time = d_time;
//         e->update();
//     }
//
//     // O(n^2) collision — this is very slow indeed, however, for pong, it works great!
//     sf::FloatRect other_box;
//     for (const auto& i : the_entities)
//     {
//         other_box = i->node_draw.sprite.getGlobalBounds();
//         for (const auto& j : the_entities)
//         {
//             sf::FloatRect boundingBox = j->node_draw.sprite.getGlobalBounds();
//
//             if (boundingBox.intersects(other_box) and j->node_draw.ID != i->node_draw.ID)
//             {
//                 i->collided();
//             }
//         }
//     }
//
// }