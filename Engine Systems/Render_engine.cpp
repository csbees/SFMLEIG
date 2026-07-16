//
// Created by chris on 6/24/26.
//

#include "Render_engine.h"
#include "Entity.h"

void Render_engine::draw_objects(sf::RenderWindow& window)
{

    for (int i = 0; i < draw_reel.size(); i++)
    {
        if (draw_reel.at(i)->flag_dead)
        {
            draw_reel.erase(draw_reel.begin() + i);
            continue;
        }
        if (draw_reel.at(i)->sprite.getPosition().x > 800 or draw_reel.at(i)->sprite.getPosition().x < -50)
            continue;
        if (draw_reel.at(i)->sprite.getPosition().y > 800 or draw_reel.at(i)->sprite.getPosition().y < -50)
            continue;
        if (draw_reel.at(i)->flag_is_animated == false)
        {
            window.draw(draw_reel.at(i)->sprite);
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




