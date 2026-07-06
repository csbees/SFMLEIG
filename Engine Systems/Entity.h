//
// Created by chris on 6/30/26.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Render_engine.h"
#include "logger.h"
#include "Draw_node.h"

class Entity
{
public:
    Draw_node node;
    logger* log = nullptr;

    sf::Vector2f entity_position;
    float delta_time = 0;

    virtual ~Entity() = default;
    /// @brief virtual function that will be called when the entity collides. Play sounds, resolve collisions, etc.
    virtual void collided() = 0;
    /// @brief virtual function that will be called every frame. Used to update things like position, collisions, etc.
    virtual void update() = 0;

    explicit Entity(Render_engine& given_r_engine, logger& given_log, const std::string& sprite_file = "-1")
    {
        log = &given_log;

        if (sprite_file == "-1")
        {
            log->log_error("Failed to load sprite, sprite_file is missing", std::to_string(node.ID));
            return;
        }
        std::cout << sprite_file << '\n';
        if (!node.texture.loadFromFile(sprite_file))
        {
            log->log_error("Failed to load sprite, loadFromFile() failed", std::to_string(node.ID));
            return;
        }
        sf::Sprite the_sprite(node.texture);
        the_sprite.setPosition(entity_position);

        given_r_engine.add_object_to_reel(node);

        node.sprite = std::move(the_sprite);
    }
};
