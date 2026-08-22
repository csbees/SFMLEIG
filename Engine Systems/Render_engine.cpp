//
// Created by chris on 6/24/26.
//

#include "Render_engine.h"
#include "Entity.h"

void Render_engine::draw_objects(sf::RenderWindow& window)
{

    for (int i = draw_reel.size() - 1; i > -1; i--)
    {
        if (draw_reel.at(i)->flag_dead)
        {
            draw_reel.erase(draw_reel.begin() + i);
            continue;
        }
        if (draw_reel.at(i)->flag_render_self == false) continue;
        if ((draw_reel.at(i)->sprite.getPosition().x > 800 or draw_reel.at(i)->sprite.getPosition().x < -50) or
           (draw_reel.at(i)->sprite.getPosition().y > 800 or draw_reel.at(i)->sprite.getPosition().y < -50))
        {
            draw_reel.at(i)->flag_being_culled = true;
            continue;
        } else draw_reel.at(i)->flag_being_culled = false;
        if (draw_reel.at(i)->flag_is_animated == false)
        {
            window.draw(draw_reel.at(i)->sprite);
            // window.draw(draw_reel.at(i)->node_hitbox.self);
            continue;
        }

        // animation code goes here

    }
}

void Render_engine::add_object_to_reel(Draw_node& node)
{
    draw_reel.push_back(&node);
    node.ID = draw_reel.size() + 1;
}

void Render_engine::reset_game()
{
    draw_reel.clear();
}





