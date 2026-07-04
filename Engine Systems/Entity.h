//
// Created by chris on 6/30/26.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "logger.h"
#include <SFML/Graphics.hpp>

#include "../Engine Systems/logger.h"
#include "../Engine Systems/Draw_node.h"

class Entity
{
public:
    explicit Entity(const std::string& sprite_file = "-1")
    {
        if (sprite_file == "-1")
        {
            log.log_error("Failed to load sprite, sprite_file is missing","Paddle()");
            return;
        } std::cout << sprite_file << '\n';
        if (!texture.loadFromFile(sprite_file))
        {
            log.log_error("Failed to load sprite, loadFromFile() failed","Paddle()");
            return;
        }
        sf::Sprite the_sprite(texture);
        the_sprite.setPosition(x_,y_);

        node.sprite = the_sprite;
    }
    virtual ~Entity() = default;
    /// @brief virtual function that will be called when the entity collides. Play sounds, resolve collisions, etc.
    virtual void collided() = 0;
    /// @brief virtual function that will be called every frame. Used to update things like position, collisions, etc.
    virtual void update() = 0;

    Draw_node node;

    // TODO: Some how only have on logger, pointer to one?
    logger log;

    float x_ = 3;
    float y_ = 100;

    float delta_time;

    sf::Sprite sprite_;
    sf::Texture texture;

};

#endif //ENTITY_H
