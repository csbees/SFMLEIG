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

        if (e->node_draw.my_type == OBJECT_TYPE::PLAYER and
                   e->label_dead == true)
        {
            player_is_dead = true;
            return;
        }
        if (e->node_draw.my_type == OBJECT_TYPE::PLAYER)
        {
            auto& e_player = dynamic_cast<Player&>(*e);
            player_lives = e_player.get_lives();
            player_shots = e_player.get_available_shots();
            player_position = e_player.node_draw.sprite.getPosition();
        }
        if (e->node_draw.my_type == OBJECT_TYPE::ASTEROID and
                   e->label_dead == true)
        {
            auto& the_asteroids = dynamic_cast<Asteroid&>(*e);
            if (the_asteroids.flag_killed_by_player == true)
                score_personal += 500;
        }

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

void Object_Manager::reset_game()
{
    all_entities.clear();
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
            // Wait, this doesn't work? WHY? ITS BEEN WORKING THOUGH
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

            if (i->node_draw.my_type == PLAYER)
            {
                auto& i_player = dynamic_cast<Player&>(*i);
                if ((i_player.i_frames > 0)) continue;
            }
            if (j->node_draw.my_type == PLAYER)
            {
                auto& j_player = dynamic_cast<Player&>(*j);
                if ((j_player.i_frames > 0)) continue;
            }

            sf::RectangleShape box = i->node_draw.node_hitbox.self;
            sf::RectangleShape other_box = j->node_draw.node_hitbox.self;

            if (box.getGlobalBounds().findIntersection(other_box.getGlobalBounds()) and j->node_draw.ID != i->node_draw.ID)
            {
                i->collided();
                j->collided();
            }
        }
    }

}

void Object_Manager::create_objects_init(Render_engine& r_engine, logger& log)
{
    create_object<Player>(r_engine, log, *this,RESOURCES_PATH + std::string("/Art/space_ship_p_V3.png"));
}
