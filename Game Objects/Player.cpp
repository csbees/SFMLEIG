//
// Created by chris on 7/6/26.
//

#include "Player.h"
#include <cmath>
#include <random>

void Player::update(float delta_time)
{
    p_delta_time = delta_time;
    const auto corrected_player_angle = (node_draw.sprite.getRotation() + sf::degrees(90));
    node_draw.sprite.setRotation(corrected_player_angle);

    if (lives < 1)
    {
        player_loses();
        return;
    }

    if (shoot_timer > 1)
    {
        shoot_timer -= 10 * p_delta_time;
    }

    calculate_movement();
    node_phy.angle_radians = node_phy.angle_degrees * (3.14159265f / 180.f);
    if (last_recorded_direction != node_phy.angle_degrees and new_movement_recorded == true)
    {
        currently_moving_direction = (last_recorded_direction + node_phy.angle_radians)/2;
    }
    velocity_x *= 0.999;
    velocity_y *= 0.999;

    velocity_turning *= 0.9;

    if  (
        (node_phy.position.x > 700) or
        (node_phy.position.x < 0)
        )
    {
        velocity_x *= -1;
        velocity_x /= 4;
    }
    if  (
        (node_phy.position.y > 700) or
        (node_phy.position.y < 0)
        )
    {
        velocity_y *= -1;
        velocity_y /= 4;
    }
    while (node_phy.position.x > 700)
    {
        node_phy.position.x -= 1;
    }
    while (node_phy.position.x < 0)
    {
        node_phy.position.x += 1;
    }
    while (node_phy.position.y > 700)
    {
        node_phy.position.y -= 1;
    }
    while (node_phy.position.y < 0)
    {
        node_phy.position.y += 1;
    }

    node_phy.position.x += velocity_x * p_delta_time;
    node_phy.position.y += velocity_y * p_delta_time;

    node_phy.general_velocity = abs(velocity_x) + abs(velocity_y);

    node_phy.angle_degrees += velocity_turning;

    last_recorded_direction = currently_moving_direction;
    if (last_recorded_direction == node_phy.angle_radians )
    {
        new_movement_recorded = false;
    }

    if (i_frames > 0) { i_frames--; }
    int iblink_frames = static_cast<int>(blink_frames);
    if ((iblink_frames % 2) == 1)
    {
        node_draw.flag_render_self = false;
    } else node_draw.flag_render_self = true;
    if (blink_frames > 0)
    {
        blink_frames -= 0.1;
    }

}

void Player::collided()
{
    if (i_frames > 0) { return; }
    blink_frames = 10.0f;
    i_frames = I_FRAMES_AMOUNT;
    lives--;
    if (lives > 0)
        sound_hit.play();
}

void Player::player_loses()
{
    if (node_draw.flag_render_self)
    {
        sound_die.setVolume(200);
        sound_die.play();
    }
    node_draw.flag_render_self = false;
    label_dead = true;
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
                velocity_turning    -= SPEED_TURNING * p_delta_time;
            }
            break;
        case sf::Keyboard::Key::D:
            {
                velocity_turning    += SPEED_TURNING * p_delta_time;
            }
            break;
        case sf::Keyboard::Key::W:
            {
                velocity_x += std::cos(currently_moving_direction) * SPEED_MOVE * p_delta_time;
                velocity_y += std::sin(currently_moving_direction) * SPEED_MOVE * p_delta_time;

                new_movement_recorded = true;
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
    shoot_timer = 2.5;

    std::mt19937 rng(std::random_device{}());
    auto random_pitch = std::uniform_int_distribution<float>(0.8, 1)(rng);

    sound_shoot.set_pitch(random_pitch);
    sound_shoot.play();

}

