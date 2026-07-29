//
// Created by chris on 7/4/26.
//

#include "Object_Manager.h"

#include "../../Game Objects/Player.h"


void Object_Manager::update_objects(float delta_time)
{
    for (auto& e : all_entities)
    {
        if (!e) continue;

        e->node_draw.sprite.setRotation(sf::degrees(e->node_phy.angle_degrees));
        e->node_draw.sprite.setPosition(sf::Vector2f(e->node_phy.position));
        e->update(delta_time);

        if (e->label_dead)
        {
            e.reset();
            break;
        }
    }

    check_collision();



    if (!pending_entities.empty())
    {
        for (auto& i : pending_entities)
        {
            all_entities.push_back(std::move(i));
        }
        pending_entities.clear(); // just in case
    }
}

void Object_Manager::check_collision() const
{
    for (const auto& i : all_entities)
    {
        if (!i) continue;
        for (const auto& j : all_entities)
        {
            if (!j) continue;
            // CHECKS
            // TODO: This doesn't work, add a flag for god mode or something
            if (i->node_draw.ID == j->node_draw.ID) continue;
            if (i->node_draw.flag_render_self == false or
                j->node_draw.flag_render_self == false)
            {
                continue;
            }
            if (i->node_draw.my_type == ASTEROID and
                j->node_draw.my_type == ASTEROID)
            {
                continue;
            }
            if (i->node_draw.my_type == BULLET and
               j->node_draw.my_type == BULLET)
            {
                continue;
            }
            if ((i->node_draw.my_type == BULLET and j->node_draw.my_type == PLAYER) or
                (j->node_draw.my_type == BULLET and i->node_draw.my_type == PLAYER))
            {
                continue;
            }

            sf::FloatRect box = i->node_draw.sprite.getGlobalBounds();
            sf::FloatRect other_box = j->node_draw.sprite.getGlobalBounds();

            if (box.findIntersection(other_box) and j->node_draw.ID != i->node_draw.ID)
            {
                i->collided();
                j->collided();
            }
        }
    }


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
