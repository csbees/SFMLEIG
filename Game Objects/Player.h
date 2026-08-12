//
// Created by chris on 7/6/26.
//

#pragma once
#include "Bullet.h"
#include "../Engine Systems/Managers/Object_Manager.h"
#include "SFML/Audio.hpp"
#include "../Engine Systems/sound_container.h"

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
    void player_loses();

    using Entity::Entity;

    Player(Render_engine& given_r_engine,
           logger& given_log,
           Object_Manager& given_obj_manager,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file), r_engine(given_r_engine), obj_manager(given_obj_manager),
          sound_shoot("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/laserShoot.wav"),
          sound_die("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/explosion.wav"),
          sound_hit("/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Music/hitHurt.wav")
    {
        node_draw.my_type = PLAYER;
        node_draw.sprite.setScale(sf::Vector2f(.1,0.1));
        node_draw.sprite.setOrigin(sf::Vector2f(250,250));

    }

    bool dead_state = false;

private:

    // Keep in mind, 60 = ~one second
    float shoot_timer = 0;
    Render_engine& r_engine;
    Object_Manager& obj_manager;
    int death_timer = 0;
    float p_delta_time = 0;

    Sound_Container sound_shoot;
    Sound_Container sound_hit;
    Sound_Container sound_die;

    float last_recorded_direction = 0;
    bool new_movement_recorded = false;
    float currently_moving_direction = 0;
    float new_velocity = 0;

    int i_frames = 0;
    const int I_FRAMES_AMOUNT = 100;
    float blink_frames = 0;

    const float SPEED_TURNING = 300;
    const float SPEED_MOVE    = 400;
    const float SPEED_MAX     = 1000;
    float velocity_x = 0;
    float velocity_y = 0;
    int lives = 3;
};

