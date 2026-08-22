//
// Created by chris on 8/18/26.
//

#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Node_Hitbox
{
public:
    explicit Node_Hitbox(const sf::Sprite& given_sprite): sprite(given_sprite)
    {
        self.setOutlineColor(outline_color);
        self.setFillColor(sf::Color::Transparent);
        self.setScale(scale);
        self.setOutlineThickness(outline_thickness);
    }

    sf::RectangleShape self;

    void update_hitbox(const sf::Vector2f position, const sf::Angle angle)
    {
        self.setPosition(position);
        self.setRotation(angle);
    }

    void set_size(const sf::Sprite& given_sprite)
    {
        self.setSize(given_sprite.getGlobalBounds().size - hitbox_transformation);
        self.setOrigin(origin + (hitbox_transformation / 2.f));
    }
    void set_size(const sf::Vector2f size)
    {
        self.setSize(size);
    }

    void set_transformations(const sf::Vector2f t)
    {
        hitbox_transformation = t;
        set_size(sprite);
    }
    void set_scale(const sf::Vector2f s)
    {
        scale = s;
        self.setScale(scale);
    }

    void set_origin(const sf::Vector2f new_origin)
    {
        origin = new_origin;
        self.setOrigin(origin);
    }
    sf::Vector2f get_origin() const
    {
        return self.getOrigin();
    }

private:
    sf::Vector2f scale;
    sf::Vector2f origin;
    const sf::Sprite& sprite;
    sf::Color outline_color = sf::Color::Red;
    float outline_thickness = 2.f;
    sf::Vector2f hitbox_transformation = {0,0};
};
