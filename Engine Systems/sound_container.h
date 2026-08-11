//
// Created by chris on 8/11/26.
// Credit goes to StackOverFlow user @bapibopi, though I did have to update the code
// to work with my version of SFML.
// See the post here: https://stackoverflow.com/questions/27235897/how-do-i-properly-organize-and-implement-sfml-audio-in-c
//

#pragma once
#include <iostream>

#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Sound_Container {

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    std::string sound_file;
public:
    explicit Sound_Container(std::string given_sound_file) : sound(buffer), sound_file(std::move(given_sound_file))
    {
        //Initialize audio
        buffer.loadFromFile(sound_file);
        sound.setBuffer(buffer);
    }

    void play()
    {
        sound.play();       // Play queued audio
    }
    void stop()
    {
        sound.stop();
    }
};
