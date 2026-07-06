//
// Created by chris on 6/24/26.
//

#include "Render_engine.h"
#include "Entity.h"

void Render_engine::draw_objects(sf::RenderWindow& window) const
{
    for (const auto& i : draw_reel)
    {
        if (i.is_animated == false)
        {
            window.draw(i.sprite);
            break;
        }

        // animation code goes here

    }
}

void Render_engine::add_object_to_reel(Draw_node& node)
{
    draw_reel.insert(draw_reel.begin(), node);
    node.ID = draw_reel.size() + 1;
}




