//
// Created by chris on 6/24/26.
//

#ifndef DRAWER_H
#define DRAWER_H
#include <vector>
#include <SfML/Graphics.hpp>

#include "Draw_node.h"
#include "../src/Paddle.h"


// TODO: Add animation support
class Render_engine
{
public:
    void draw_objects(sf::RenderWindow& window) const;

    // TODO: make this automatic when creating and Entity
    void add_object_to_reel(Entity& e);

    void find_collision(float d_time) const;

private:

    // Contains all the Draw_nodes that will be drawn this frame
    // Draws from back to front, meaning the first thing added will the be first thing drawn
    // Use std::vector::insert to add to the front
    // TODO: FIX THIS DANGEROUS THING, BRUH, RAW POINTS? NAHHH
    std::vector<Draw_node*> draw_reel;
    std::vector<Entity*> the_entities;


};



#endif //DRAWER_H
