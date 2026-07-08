//
// Created by chris on 7/6/26.
//

#pragma once
#include "Bullet.h"

class Player : public Entity
{
    void update() override;
    void collided() override;

    // TODO: Add keymapping (much later though)
    // I may add this to entity
    [[nodiscard]] std::vector<sf::Keyboard::Key> check_for_input();
    void calculate_movement();
    void shoot();

    using Entity::Entity;

private:
    // holds all the bullets the player has shot
    std::vector<std::unique_ptr<Bullet>> players_bullets;
};

