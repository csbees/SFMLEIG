//
// Created by chris on 7/6/26.
//

#include "Asteroid.h"

void Asteroid::collided()
{
    if (just_took_damage > 1) return;
    health--;
    if (health < 1)
    {
        flag_killed_by_player = true;
        die();
    }
    just_took_damage = 2;
}
void Asteroid::die()
{
    node_draw.flag_dead = true;
    label_dead = true;
}


void Asteroid::update(float delta_time)
{
    if (just_took_damage > 1) just_took_damage--;

    if (node_draw.flag_being_culled == false)
        entered_player_area_yet = true;
    if (node_draw.flag_being_culled == true && entered_player_area_yet == true)
    {
        die();
        return;
    }

    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);

    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity) * delta_time;

    node_draw.sprite.setRotation(sf::degrees(node_phy.angle_degrees));
    node_draw.sprite.setPosition(sf::Vector2f(node_phy.position));

    node_draw.node_hitbox.update_hitbox(node_phy.position,sf::degrees(node_phy.angle_degrees));

}

