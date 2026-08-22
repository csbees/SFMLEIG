//
// Created by chris on 7/6/26.
//

#pragma once
#include <random>

#include "../Engine Systems/Entity.h"

class Asteroid_Manager;

class Asteroid : public Entity
{
public:
    Asteroid(Render_engine& given_r_engine,
           logger& given_log,
           const Physics_node& asteroid_phy_node,
           const std::string& sprite_file = "-1",
           Asteroid_Manager* given_asteroid_manager = nullptr,
           int given_asteroid_type = 1,
           float given_scale_facter = 0.1)
        : Entity(given_r_engine, given_log, sprite_file)
    {
    asteroid_manager_ = given_asteroid_manager;

        node_phy.position = asteroid_phy_node.position;
        node_phy.angle_degrees = asteroid_phy_node.angle_degrees;
        node_phy.general_velocity = asteroid_phy_node.general_velocity;
        node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));

        std::mt19937 rng(std::random_device{}());
        const auto added_scale = std::uniform_real_distribution<float>(0.f, 0.07f)(rng);
        const auto random_rotation = std::uniform_real_distribution<float>(0.f, 360.f)(rng);
        node_draw.origin = {270,270};
        node_draw.scale = {given_scale_facter,given_scale_facter};
        sf::Vector2f hitbox_transformation = {270,270};

        node_draw.node_hitbox.set_transformations(hitbox_transformation);
        node_draw.node_hitbox.set_size(node_draw.sprite);
        node_draw.node_hitbox.set_scale({node_draw.scale.x + added_scale, node_draw.scale.y + added_scale});
        node_draw.node_hitbox.set_origin({node_draw.node_hitbox.get_origin().x + 60, node_draw.node_hitbox.get_origin().y});


        node_draw.my_type = ASTEROID;
        node_draw.sprite.setScale({node_draw.scale.x + added_scale, node_draw.scale.y + added_scale});
        node_draw.sprite.setOrigin(node_draw.origin);
        node_draw.sprite.setRotation(sf::degrees(random_rotation));
        FACE_THIS_WAY = random_rotation;

        asteroid_type = given_asteroid_type;

        health = DEFAULT_HEATH; //* (given_scale_facter * 10);
    }

    void update(float) override;

    bool flag_killed_by_player = false;

private:
    int asteroid_type; // 1 - big, 2 - medium , 3 - small
    Asteroid_Manager* asteroid_manager_;
    int health;
    const int DEFAULT_HEATH = 2;
    bool entered_player_area_yet = false;
    int just_took_damage = 0;
    float FACE_THIS_WAY = 0;
    void collided() override;
    void die();
};
