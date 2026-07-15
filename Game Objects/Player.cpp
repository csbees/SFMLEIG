//
// Created by chris on 7/6/26.
//

#include "Player.h"

void Player::update()
{
    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);

    calculate_movement();
    node_phy.general_velocity *= 0.9999;
    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity); //* delta_time_seconds;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity); //* delta_time_seconds;

    for (auto& b : players_bullets)
    {
        b->update();
    }
    if (shoot_timer > 1) shoot_timer -= 1;// * delta_time;
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
                node_phy.angle_degrees -= 1.1;
                std::cout << "angle" << node_phy.angle_degrees << '\n';
            }
            break;
        case sf::Keyboard::Key::D:
            {
                node_phy.angle_degrees += 1.1;
                std::cout << "angle" << node_phy.angle_degrees << '\n';

            }
            break;
        case sf::Keyboard::Key::W:
            {
                node_phy.general_velocity += 0.005;
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
    auto bullet = std::make_unique<Bullet>(r_engine, log, node_phy ,"/Users/chris/CLionProjects/Engine/SFMLEIG 1.0/Assets/Art/Plane.png");
    players_bullets.push_back(std::move(bullet));
    shoot_timer = 20;
}

