//
// Created by chris on 7/6/26.
//

#pragma once
#include "Bullet.h"

class Player : public Entity
{
public:
    void update() override;
    void collided() override;

    // TODO: Add keymapping (much later though)
    // I may add this to entity
    [[nodiscard]] std::vector<sf::Keyboard::Key> check_for_input();
    void calculate_movement();
    void shoot();

    using Entity::Entity;

    Player(Render_engine& given_r_engine,
           logger& given_log,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file), r_engine(given_r_engine)
    {
        node_draw.my_name = "Player";
    }

private:

    // Keep in mind, 60 = ~one second
    float shoot_timer = 0;
    Render_engine& r_engine;
    // holds all the bullets the player has shot
    std::vector<std::unique_ptr<Bullet>> players_bullets;
};

