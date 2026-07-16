//
// Created by chris on 7/4/26.
//

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include "../Entity.h"

/* OBJECT OWNERSHIP AND RESPONSIBILITIES
 * Owns ALL Entities
 * Updates ALL Entities
 */
class Object_Manager
{
public:
    explicit Object_Manager(Render_engine& given_r_engine)
        : r_engine(given_r_engine) {}

    void update_objects(float delta_time);
    void check_collision();
    void create_objects_init(Render_engine& r_engine, logger& log);

    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log,  const std::string& sprite_file)
    {
        auto new_obj = std::make_unique<T>(given_r_engine, log, sprite_file);
        all_entities.push_back(std::move(new_obj));
    }
    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log, Physics_node phy_node, const std::string& sprite_file)
    {
        auto new_obj = std::make_unique<T>(given_r_engine, log, phy_node, sprite_file);
        all_entities.push_back(std::move(new_obj));
    }
    template <typename T>
    inline void create_object(Render_engine& given_r_engine, logger& log, Object_Manager& given_obj_manager, const std::string& sprite_file)
    {
        auto new_obj = std::make_unique<T>(given_r_engine, log, given_obj_manager, sprite_file);
        all_entities.push_back(std::move(new_obj));
    }
private:
    // Owns all Entities
    std::vector<std::unique_ptr <Entity>> all_entities;
    Render_engine& r_engine;

    bool player_died = false;
};



#endif //OBJECT_MANAGER_H
