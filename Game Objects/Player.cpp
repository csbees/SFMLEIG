//
// Created by chris on 7/6/26.
//

#include "Player.h"

void Player::update()
{
    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);

    calculate_movement();
    node_phy.general_velocity *= 0.999999;
    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity); //* delta_time_seconds;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity); //* delta_time_seconds;
}

void Player::collided()
{

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

    return keys_pressed;
}

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
        default:
            std::cout << "Another button was pressed\n";
            break;
        }
    }
    keys_pressed.clear();
}



