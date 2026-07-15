//
// Created by chris on 7/4/26.
//

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include "../Entity.h"
#include "../../Game Objects/Asteroid_Manager.h"
#include "../../Game Objects/Player.h"

/* OBJECT OWNERSHIP AND RESPONSIBILITIES
 * Owns all parent Entities
 * Updates all parent Entities
 */
class Object_Manager
{
public:
    void find_collision(const float d_time) const; // I'm not sure if I'm even going to have the obj manager do it
    // Iterates through all objects, and runs there update() function.
    void update_objects(Player player, Asteroid_Manager Aster) const;
    void create_game_objects(Render_engine& r_engine, logger& log);

    // Owns all Entities
    std::vector<std::unique_ptr<Entity>> the_entities;
};



#endif //OBJECT_MANAGER_H
