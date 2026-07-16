//
// Created by chris on 7/6/26.
//

#include "Player.h"

void Player::update(float delta_time)
{
    p_delta_time = delta_time;

    // TODO: UPDATE this with collided()
    // if (node_draw.hit_something == true)
    // {
    //     got_hit();
    //     node_draw.hit_something = false;
    // }
    if (dead_state == true)
    {
        if (death_timer < 1)
        {
            dead_state = false;
            node_draw.flag_render_self = true;
        }
        else death_timer--;
        return;
    }
    if (shoot_timer > 1)
    {
        shoot_timer -= 1 * p_delta_time;
    }

    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);

    calculate_movement();
    node_phy.general_velocity *= 0.9999;
    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity) * p_delta_time;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity) * p_delta_time;

}

void Player::got_hit()
{
    lives--;
    if (lives < 1)
    {
        // I'll send the players back to the menu;
        return;
    }
    // otherwise, all bullets will be destroyed, the player will play a explosion animation of some kind (fake animation)
    // they will be invincible for a few seconds -> Tped to spawn, invincibility over.
    std::cout << "The player has been hit\n";
    // death_timer = 500;
    // node_draw.flag_render_self = false;
    // dead_state = true;
}

void Player::collided()
{
    std::cout << "I hit something!\n";
}

std::vector<sf::Keyboard::Key> Player::check_for_input()
{
    std::vector<sf::Keyboard::Key> keys_pressed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        keys_pressed.push_back(sf::Keyboard::Key::W);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        keys_pressed.push_back(sf::Keyboard::Key::D);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        keys_pressed.push_back(sf::Keyboard::Key::A);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        keys_pressed.push_back(sf::Keyboard::Key::Space);
    }

    return keys_pressed;
}

// I want the player to be able to turn, but not move in that direction when they turn.
void Player::calculate_movement()
{
    auto keys_pressed = check_for_input();

    for (auto i : keys_pressed)
    {
        switch (i)
        {
        case sf::Keyboard::Key::A:
            {
                node_phy.angle_degrees    -= SPEED_TURNING * p_delta_time;
            }
            break;
        case sf::Keyboard::Key::D:
            {
                node_phy.angle_degrees    += SPEED_TURNING * p_delta_time;
            }
            break;
        case sf::Keyboard::Key::W:
            {
                node_phy.general_velocity += SPEED_MOVE;
            }
            break;
        case sf::Keyboard::Key::Space:
            shoot();
            break;
        default:
            std::cout << "Another button was pressed\n";
            break;
        }
    }
    keys_pressed.clear();
}

void Player::shoot()
{
    if (shoot_timer > 1) return;
    obj_manager.create_object<Bullet>(r_engine, log, node_phy ,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
    shoot_timer = 20;
}

