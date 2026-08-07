//
// Created by chris on 7/4/26.
//

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include "../Entity.h"
#include "../../Game Objects/Asteroid.h"

class Asteroid_Manager;


/* OBJECT OWNERSHIP AND RESPONSIBILITIES
 * Owns ALL Entities
 * Updates ALL Entities
 */
class Object_Manager
{
public:
    explicit Object_Manager(Render_engine& given_r_engine)
        : r_engine(given_r_engine) { }

    void update_objects(float delta_time);
    void check_collision() const;
    void create_objects_init(Render_engine& r_engine, logger& log);

    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log,  const std::string& sprite_file)
    {
        pending_entities.push_back(std::move( std::make_unique<T>(given_r_engine, log, sprite_file)));
    }
    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log, Physics_node phy_node, const std::string& sprite_file)
    {
        pending_entities.push_back(std::move(std::make_unique<T>(given_r_engine, log, phy_node, sprite_file)));
    }
    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log, Object_Manager& given_obj_manager, const std::string& sprite_file)
    {
        pending_entities.push_back(std::move(std::make_unique<T>(given_r_engine, log, given_obj_manager, sprite_file)));
    }
    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log, Physics_node phy_node, const std::string& sprite_file, Asteroid_Manager* given_asteroid_manager, int asteroid_type)
    {
        pending_entities.push_back(std::move(
            std::make_unique<T>(given_r_engine, log, phy_node, sprite_file, given_asteroid_manager, asteroid_type)));
    }

//private:
    // Owns all Entities
    std::vector<std::unique_ptr <Entity>> all_entities;
    // All entities going to be created.
    // I have to do this, so I don't put things in all_entities while iterating over all_entities
    std::vector<std::unique_ptr <Entity>> pending_entities;
    Render_engine& r_engine;

    bool player_died = false;
};



#endif //OBJECT_MANAGER_H
