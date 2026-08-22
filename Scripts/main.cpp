
#include "../Game Objects/Asteroids_Game.h"
#include "../Engine Systems/resource_path.h"

int main()
{
    initialize_resource_path();

    Asteroids_Game game;
    game.run_game();
}