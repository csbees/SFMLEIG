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

    if (shoot_timer > 1) { shoot_timer -= 10 * p_delta_time; }
     if (timer_reload > -2)
    {
         timer_reload--;
         if (timer_reload < 1) {my_bullets = 16; }
     }
    if (sound_engine.get_volume() > 0) sound_engine.setVolume(sound_engine.get_volume() - 100);
    if (sound_engine.get_volume() < 0) sound_engine.setVolume(0);

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

    node_draw.node_hitbox.update_hitbox(node_phy.position,sf::degrees(node_phy.angle_degrees));

    booster_left.update(node_draw.sprite.getPosition(), node_phy.angle_degrees + 90, booster_left.showing,
        {node_draw.origin.x- 40,node_draw.origin.y- 510}, blink_frames);
    booster_right.update(node_draw.sprite.getPosition(), node_phy.angle_degrees + 90, booster_right.showing,
        {node_draw.origin.x- 400,node_draw.origin.y- 510}, blink_frames);

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
        sound_die.setVolume(90);
        sound_die.play();
    }
    sound_engine.setVolume(0);
    node_draw.flag_render_self = false;
    label_dead = true;
    booster_left.node_draw.sprite.setPosition({-100,-100});
    booster_right.node_draw.sprite.setPosition({-100,-100});
}

// void Player::play_boosters()
// {
//     if (timer_booster > 1) return;
//     for (auto& s : booster_sounds)
//     {
//         if (s.get_status() != sf::SoundSource::Status::Playing)
//         {
//             s.play();
//             timer_booster = 4;
//             std::cout << "played sound\n";
//             return;
//         }
// }

std::vector<sf::Keyboard::Key> Player::check_for_input()
{
    std::vector<sf::Keyboard::Key> keys_pressed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        keys_pressed.push_back(sf::Keyboard::Key::W);
    } else if (boosters_showing == 2)
    {
        booster_right.showing = false;
        booster_left.showing = false;
        boosters_showing = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        keys_pressed.push_back(sf::Keyboard::Key::D);
    } else if (boosters_showing == 3)
    {
        boosters_showing = 0;
        booster_left.showing = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        keys_pressed.push_back(sf::Keyboard::Key::A);
    } else if (boosters_showing == 1)
    {
        boosters_showing = 0;
        booster_right.showing = false;
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
        if (i == sf::Keyboard::Key::W)
        {
            booster_right.showing = true;
            booster_left.showing = true;
            boosters_showing = 2;
        } else if (i == sf::Keyboard::Key::A)
        {
            booster_right.showing = true;
            if ((boosters_showing != 2) or (boosters_showing != 3)) boosters_showing = 1;
        }
        else if ((i == sf::Keyboard::Key::D))
        {
            booster_left.showing = true;
            if ((boosters_showing != 2) or (boosters_showing != 1))  boosters_showing = 3;
        }


        switch (i)
        {
        case sf::Keyboard::Key::A:
            {
                velocity_turning    -= SPEED_TURNING * p_delta_time;
                if (sound_engine.get_volume() < 170)
                    sound_engine.setVolume(sound_engine.get_volume() + 170);
            }
            break;
        case sf::Keyboard::Key::D:
            {
                velocity_turning    += SPEED_TURNING * p_delta_time;
                if (sound_engine.get_volume() < 100)
                    sound_engine.setVolume(sound_engine.get_volume() + 100);
            }
            break;
        case sf::Keyboard::Key::W:
            {
                velocity_x += std::cos(currently_moving_direction) * SPEED_MOVE * p_delta_time;
                velocity_y += std::sin(currently_moving_direction) * SPEED_MOVE * p_delta_time;

                if (sound_engine.get_volume() < 300)
                    sound_engine.setVolume(sound_engine.get_volume() + 300);

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
    if (my_bullets < 1) return;
    if (shoot_timer > 1) return;
    obj_manager.create_object<Bullet>(r_engine, log, node_phy ,RESOURCES_PATH + std::string("Art/Bullet_V3.png"));
    shoot_timer = 2.5;

    std::mt19937 rng(std::random_device{}());
    auto random_pitch = std::uniform_int_distribution<float>(0.8, 1)(rng);

    sound_shoot.set_pitch(random_pitch);
    sound_shoot.play();
    my_bullets--;
    if (my_bullets < 1) timer_reload = RELOAD_TIME;


}

void Boosters::update(sf::Vector2f position, float angle_degrees, bool given_showing, sf::Vector2f origin, float blink_frames)
{
    showing = given_showing;
    if (showing == false)
        node_draw.flag_render_self = false;
    else
        node_draw.flag_render_self = true;

    int iblink_frames = static_cast<int>(blink_frames);
    if ((iblink_frames % 2) == 1 and node_draw.flag_render_self == true)
    {
        node_draw.flag_render_self = false;
    }
    if (blink_frames > 0)
    {
        blink_frames -= 0.1;
    }

    node_draw.sprite.setPosition(position);
    node_draw.sprite.setRotation(sf::degrees(angle_degrees));
    node_draw.sprite.setOrigin(origin);
}

void Boosters::collided()
{

}

void Boosters::update(float delta_time)
{

}



