//
// Created by chris on 6/24/26.
//

#include "Render_engine.h"
#include "Entity.h"

void Render_engine::draw_objects(sf::RenderWindow& window) const
{
    for (const auto& i : draw_reel)
    {
        if (i->is_animated == false)
        {
            window.draw(i->sprite);
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




