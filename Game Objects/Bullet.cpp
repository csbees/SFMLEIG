//
// Created by chris on 7/6/26.
//

#include "Bullet.h"
void Bullet::collided()
{

}

void Bullet::update(float delta_time)
{
    // std::cout << "position : " << node_phy.position.x << ' ' << node_phy.position.y << '\n'
    //                   << "Rotation :"  << node_phy.angle_degrees << "\n"
    //                   << "Velo     :"  << node_phy.general_velocity << "\n\n";

    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;

    node_draw.sprite.setRotation(sf::degrees(node_phy.angle_degrees));
    node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));
}

