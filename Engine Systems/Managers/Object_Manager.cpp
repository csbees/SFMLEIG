//
// Created by chris on 7/4/26.
//

#include "Object_Manager.h"

#include "../../Game Objects/Player.h"


void Object_Manager::update_objects(float delta_time)
{
    for (auto& e : all_entities)
    {
        e->node_draw.sprite.setRotation(sf::degrees(e->node_phy.angle_degrees));
        e->node_draw.sprite.setPosition(sf::Vector2f(e->node_phy.position));
        e->update(delta_time);
    }

}

void Object_Manager::check_collision()
{
    // for (const auto& i : r_engine.draw_reel)
    // {
    //
    //     sf::FloatRect other_box = i->sprite.getGlobalBounds();
    //     for (const auto& j : r_engine.draw_reel)
    //     {
    //         if ((i->my_name == "Player" or j->my_name == "Player") and
    //             (i->flag_render_self == false or j->flag_render_self == false))
    //         {
    //             continue;
    //         }
    //
    //
    //
    //         sf::FloatRect boundingBox = j->sprite.getGlobalBounds();
    //
    //         if (i->my_name == "asteroid" and j->my_name == "asteroid")
    //             continue;
    //         if (i->my_name == "bullet" and j->my_name == "bullet")
    //             continue;
    //         if ((i->my_name == "bullet" and j->my_name == "Player") or (i->my_name == "Player" and j->my_name == "bullet"))
    //             continue;
    //
    //         if (boundingBox.findIntersection(other_box) and j->ID != i->ID)
    //         {
    //             if ((i->my_name == "Player" and j->my_name == "asteroid") or (i->my_name == "asteroid" and j->my_name == "Player"))
    //             {
    //                 std::cout << "player hit asteroid\n";
    //                 i->hit_something = true;
    //                 j->hit_something = true;
    //             }
    //
    //             else if ((i->my_name == "bullet" and j->my_name == "asteroid") or (i->my_name == "asteroid" and j->my_name == "bullet"))
    //             {
    //                 std::cout << "bullet hit asteroid\n";
    //                 i->hit_something = true;
    //                 j->hit_something = true;
    //             }
    //         }
    //     }
    // }
}



void Object_Manager::create_objects_init(Render_engine& r_engine, logger& log)
{
    create_object<Player>(r_engine, log, *this,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
}



// Collision need to be rewritten anyway, so commented this out for now.
// I think I want this to happen in update()
// void Object_Manager::find_collision(const float d_time) const
// {
//     for (const auto e : all_entities)
//     {
//         e->node_draw_draw.sprite.setPosition(e->x_,e->y_);
//         e->delta_time = d_time;
//         e->update();
//     }
//
//     // O(n^2) collision — this is very slow indeed, however, for pong, it works great!
//     sf::FloatRect other_box;
//     for (const auto& i : all_entities)
//     {
//         other_box = i->node_draw.sprite.getGlobalBounds();
//         for (const auto& j : all_entities)
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