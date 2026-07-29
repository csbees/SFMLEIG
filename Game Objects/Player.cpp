//
// Created by chris on 7/6/26.
//

#include "Player.h"
#include <math.h>

void Player::update(float delta_time)
{
    p_delta_time = delta_time;

    if (lives < 1)
    {
        player_loses();
        return;
    }

    if (shoot_timer > 1)
    {
        shoot_timer -= 10 * p_delta_time;
    }

    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);

    calculate_movement();
    node_phy.general_velocity *= 0.9999;
    node_phy.position.x += std::cos(node_phy.angle_radians) * (node_phy.general_velocity) * p_delta_time;
    node_phy.position.y += std::sin(node_phy.angle_radians) * (node_phy.general_velocity) * p_delta_time;

    if (i_frames > 0) { i_frames--; }
    int iblink_frames = static_cast<int>(blink_frames);
    if ((iblink_frames % 2) == 1)
    {
        node_draw.flag_render_self = false;
        std::cout << "don't render\n";
    } else node_draw.flag_render_self = true;
    if (blink_frames > 0)
    {
        blink_frames -= 0.01;
        /*std::cout << blink_frames << '\n'
                  << "result of % " << (iblink_frames % 2) << "\n";*/

    }

}

void Player::got_hit()
{
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
    if (i_frames > 0) { return; }
    std::cout << "I hit something!\n";
    blink_frames = 5.0f;
    i_frames = I_FRAMES_AMOUNT;
    lives--;

}

void Player::player_loses()
{
    std::cout << "Lol you lose.\n";
    node_draw.flag_render_self = false;
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
    for (auto& e : obj_manager.all_entities)
        std::cout << ": " << e << ' ';
    std::cout << "size " << obj_manager.all_entities.size() << "\n";
    shoot_timer = 20;


}

