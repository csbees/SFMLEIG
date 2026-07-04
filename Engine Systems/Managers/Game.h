//
// Created by chris on 7/4/26.
//

#ifndef GAME_H
#define GAME_H

// The Owner of everything in the game. Override Game with your own game, and put it in /Game Objects
class Game
{
public:
    // Runs the game
    virtual void run_game();
    virtual ~Game() {}

};

#endif //GAME_H
