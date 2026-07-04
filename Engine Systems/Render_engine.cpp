//
// Created by chris on 6/24/26.
//

#include "Render_engine.h"



void Render_engine::draw_objects(sf::RenderWindow& window) const
{
    for (const auto& i : draw_reel)
    {
        window.draw(i->sprite);
    }
}

void Render_engine::add_object_to_reel(Entity& e)
{
    draw_reel.insert(draw_reel.begin(), &e.node);
    e.node.ID = draw_reel.size() + 1;

    the_entities.insert(the_entities.begin(), &e);
}


void Render_engine::find_collision(const float d_time) const
{
    for (const auto e : the_entities)
    {
        e->node.sprite.setPosition(e->x_,e->y_);
        e->delta_time = d_time;
        e->update();
    }

    // O(n^2) collision — this is very slow indeed, however, for pong, it works great!
    sf::FloatRect other_box;
    for (const auto& i : the_entities)
    {
        other_box = i->node.sprite.getGlobalBounds();
        for (const auto& j : the_entities)
        {
            sf::FloatRect boundingBox = j->node.sprite.getGlobalBounds();

            if (boundingBox.intersects(other_box) and j->node.ID != i->node.ID)
            {
                i->collided();
            }
        }
    }

}


