//
// Created by chris on 7/6/26.
//

#pragma once
#include "Bullet.h"
#include "../Engine Systems/Managers/Object_Manager.h"
#include "SFML/Audio.hpp"
#include "../Engine Systems/sound_container.h"

class Boosters : public Entity
{
    using Entity::Entity;

    void update(float delta_time) override;
    void collided() override;

public:
    void update(sf::Vector2f position, float angle_degrees, bool given_showing, sf::Vector2f origin, float blink_frames);
    bool showing = false;
};

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
    void player_loses();
    void play_boosters();

    using Entity::Entity;

    Player(Render_engine& given_r_engine,
           logger& given_log,
           Object_Manager& given_obj_manager,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file), r_engine(given_r_engine), obj_manager(given_obj_manager),
          sound_shoot(RESOURCES_PATH + std::string("/Music/laserShoot.wav")),
          sound_die(RESOURCES_PATH + std::string("/Music/death_soundV3.mp3")),
          sound_hit(RESOURCES_PATH + std::string("/Music/hitHurt.wav")),
          sound_engine(RESOURCES_PATH + std::string("/Music/Engine_sound_v4.wav")),
          booster_right(r_engine, log, RESOURCES_PATH + std::string("/Art/booster.png")),
          booster_left(r_engine, log, RESOURCES_PATH + std::string("/Art/booster.png"))

    {
        node_phy.position.x = 350;
        node_phy.position.y = 450;
        node_draw.sprite.setPosition({node_phy.position.x, node_phy.position.y});
        const auto corrected_player_angle = (node_draw.sprite.getRotation() + sf::degrees(90));
        node_draw.sprite.setRotation(corrected_player_angle);

        node_draw.my_type = PLAYER;
        node_draw.origin = {250, 250};
        node_draw.scale = {0.1, 0.1};
        sf::Vector2f hitbox_transformation = {200, 200};

        node_draw.node_hitbox.set_transformations(hitbox_transformation);
        node_draw.node_hitbox.set_size(node_draw.sprite);
        node_draw.node_hitbox.set_scale(node_draw.scale);
        node_draw.node_hitbox.set_origin({
            node_draw.node_hitbox.get_origin().x + 60, node_draw.node_hitbox.get_origin().y
        });

        node_draw.sprite.setOrigin(node_draw.origin);
        node_draw.sprite.setScale(node_draw.scale);

        sound_hit.setVolume(7);
        sound_shoot.setVolume(10);
        sound_die.setVolume(15);

        sound_engine.setVolume(0);
        sound_engine.play();
        sound_engine.set_looping(true);

        booster_left.node_draw.sprite.setScale({0.1,0.1});
        booster_right.node_draw.sprite.setScale({0.1,0.1});
        booster_left.node_draw.sprite.setPosition({-100,-100});
        booster_right.node_draw.sprite.setPosition({-100,-100});
    }

    inline int get_lives() const            { return  lives; }
    inline  int get_available_shots() const { return my_bullets; }

    bool dead_state = false;
    int i_frames = 0;

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
    Sound_Container sound_engine;

    Boosters booster_right;
    Boosters booster_left;
    bool show_right_b = true;
    bool show_left_b  = true;
    int boosters_showing = 0;

    std::vector<Sound_Container> booster_sounds;
    int timer_booster = 0;

    float last_recorded_direction = 0;
    bool new_movement_recorded = false;
    float currently_moving_direction = 0;
    float new_velocity = 0;

    const int I_FRAMES_AMOUNT = 100;
    float blink_frames = 0;

    const float SPEED_TURNING = 50;
    const float SPEED_MOVE    = 400;
    const float SPEED_MAX     = 1000;
    float velocity_x = 0;
    float velocity_y = 0;
    float velocity_turning = 0;

    int shots_available = AMOUNT_PLAYER_BULLETS;
    int my_bullets = 16;
    int timer_reload = 0;
    const int RELOAD_TIME = 170;
    const int AMOUNT_PLAYER_BULLETS = 9;

    const int STARTING_LIVES = 5;
    int lives = STARTING_LIVES;
};

