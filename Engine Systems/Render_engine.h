//
// Created by chris on 6/24/26.
//

#pragma once

#include <vector>
#include <SfML/Graphics.hpp>

#include "Draw_node.h"

class Entity;

class Render_engine
{
public:
    void draw_objects(sf::RenderWindow& window) const;

    void add_object_to_reel(Draw_node& node);

    void find_collision(float d_time) const;

private:

    // Contains all the Draw_nodes that will be drawn this frame
    // Draws from back to front, meaning the first thing added will the be first thing drawn
    // Use std::vector::insert to add to the front
    std::vector<Draw_node> draw_reel;


};
