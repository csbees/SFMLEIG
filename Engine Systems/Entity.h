//
// Created by chris on 6/30/26.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Render_engine.h"
#include "logger.h"
#include "Draw_node.h"

struct Physics_node
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float general_velocity = 0;
    float angle_degrees = 0;
    float angle_radians = 0;
};

class Entity
{
public:
    Draw_node node_draw  ;
    Physics_node node_phy;
    logger* log = nullptr;

    float delta_time = 0;


    virtual ~Entity() = default;
    /// @brief virtual function that will be called when the entity collides. Play sounds, resolve collisions, etc.
    virtual void collided() = 0;
    /// @brief virtual function that will be called every frame. Used to update things like position, collisions, etc.
    virtual void update() = 0;


    explicit Entity(Render_engine& given_r_engine, logger& given_log, const std::string& sprite_file = "-1")
    {
        std::cout << "Entity Created\n";
        log = &given_log;

        if (sprite_file == "-1")
        {
            log->log_error("Failed to load sprite, sprite_file is missing", std::to_string(node_draw.ID));
            throw std::runtime_error("Failed to load sprite, sprite_file is missing");
        }
        std::cout << sprite_file << '\n';
        if (!node_draw.texture.loadFromFile(sprite_file))
        {
            log->log_error("Failed to load sprite, loadFromFile() failed", std::to_string(node_draw.ID));
            throw std::runtime_error("Failed to load sprite, loadFromFile() failed");
        }
        node_draw.sprite = sf::Sprite(node_draw.texture);
        node_draw.sprite.setPosition(node_phy.position);

        given_r_engine.add_object_to_reel(node_draw);


    }

};
