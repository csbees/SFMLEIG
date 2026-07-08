//
// Created by chris on 7/4/26.
//

#pragma once

// The Owner of everything in the game. Override Game with your own game, and put it in /Game Objects
class Game
{
public:
    // Runs the game
    virtual void run_game() = 0;
    virtual void init() = 0;

    virtual ~Game() {}

};

