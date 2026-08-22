//
// Created by chris on 7/6/26.
//
#pragma once

#include <random>

#include "../Engine Systems/Entity.h"
#include "../Engine Systems/sound_container.h"
#include "../Engine Systems/resource_path.h"

class Bullet final : public Entity
{
public:
    void update(float) override;
    void collided() override;

    Bullet(Render_engine& given_r_engine,
           logger& given_log,
           const Physics_node& players_phy_node,
           const std::string& sprite_file = "-1")
        : Entity(given_r_engine, given_log, sprite_file),
          sound_hit(RESOURCES_PATH + std::string("/Music/bullet_hit_thing.wav"))
    {
        node_phy.position = players_phy_node.position;
        node_phy.angle_radians = players_phy_node.angle_radians;
        node_phy.angle_degrees = players_phy_node.angle_degrees;
        node_phy.general_velocity = BULLET_SPEED + players_phy_node.general_velocity;
        // node_phy.general_velocity = 0;

        node_draw.my_type = BULLET;
        node_draw.origin = {50,25};
        node_draw.scale = {0.5,0.5};
        // sf::Vector2f hitbox_transformation = {200,200};

        // node_draw.node_hitbox.set_transformations(hitbox_transformation);
        node_draw.node_hitbox.set_size({50,100});
        node_draw.node_hitbox.set_scale(node_draw.scale);
        node_draw.node_hitbox.set_origin({25, 50});
        // node_draw.node_hitbox.set_origin({node_draw.node_hitbox.get_origin().x + 60, node_draw.node_hitbox.get_origin().y});

        node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));
        node_draw.sprite.setRotation(sf::radians(node_phy.angle_radians - 1.570796));
        node_draw.sprite.setScale(node_draw.scale);
        node_draw.sprite.setOrigin(node_draw.origin);

        std::mt19937 rng(std::random_device{}());
        auto random_pitch = std::uniform_real_distribution<float>(0.8, 1)(rng);

        sound_hit.set_pitch(random_pitch);
        sound_hit.setVolume(15.f);


    }

private:
    const float BULLET_SPEED = 1000;
    Sound_Container sound_hit;
};
