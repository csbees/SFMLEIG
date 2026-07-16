//
// Created by chris on 7/6/26.
//

#pragma once
#include "Bullet.h"
#include "../Engine Systems/Managers/Object_Manager.h"

class Player : public Entity
{
public:
    void update(float) override;
    void collided() override;

    // TODO: Add keymapping (much later though)
    // I may add this to entity
    [[nodiscard]] std::vector<sf::Keyboard::Key> check_for_input();
    void calculate_movement();
    void shoot();
    void got_hit();
    void destroy_bullets();

    using Entity::Entity;

    Player(Render_engine& given_r_engine,
           logger& given_log,
           Object_Manager& given_obj_manager,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file), r_engine(given_r_engine), obj_manager(given_obj_manager)
    {
        node_draw.my_type = PLAYER;
    }

    bool dead_state = false;

private:

    // Keep in mind, 60 = ~one second
    float shoot_timer = 0;
    Render_engine& r_engine;
    Object_Manager& obj_manager;
    int death_timer = 0;
    float p_delta_time = 0;

    const float SPEED_TURNING = 100;
    const float SPEED_MOVE    = 1;
    int lives = 3;
};

