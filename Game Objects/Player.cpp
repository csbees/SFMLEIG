//
// Created by chris on 7/6/26.
//

#include "Player.h"

void Player::update()
{
    calculate_movement();
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
            std::cout << "A has been pressed\n";
            break;
        case sf::Keyboard::Key::D:
            std::cout << "D has been pressed\n";
            break;
        case sf::Keyboard::Key::W:
            std::cout << "W has been pressed\n";
            break;
        default:
            std::cout << "Another button was pressed\n";
            break;
        }
    }
    keys_pressed.clear();
}



