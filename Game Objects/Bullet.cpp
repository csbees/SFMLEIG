//
// Created by chris on 7/6/26.
//

#include "Bullet.h"
void Bullet::collided()
{
    node_draw.flag_dead = true;
    label_dead = true;
}

void Bullet::update(float delta_time)
{
    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;

    node_draw.sprite.setRotation(sf::radians(node_phy.angle_radians - 1.570796));
    node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));

    node_draw.hit_box.setPosition(node_phy.position);
    node_draw.hit_box.setRotation(sf::degrees(node_phy.angle_degrees));


}

