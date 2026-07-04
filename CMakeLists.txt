cmake_minimum_required(VERSION 3.29.1)

project(SFMLEIG)

target_link_libraries(
      ${CMAKE_PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

add_subdirectory(Third\ Party/SFML-3.0.0)

add_executable(
     ${CMAKE_PROJECT_NAME}
        Scripts/main.cpp
        # ENGINE ———
        "Engine Systems/logger.cpp"
        "Engine Systems/logger.h"
        "Engine Systems/Draw_node.h"
        "Engine Systems/Entity.h"
        "Engine Systems/Render_engine.h"
        "Engine Systems/Render_engine.cpp"
        "Engine Systems/Managers/Game.cpp"
        "Engine Systems/Managers/Game.h"
        "Engine Systems/Managers/Menu_Manager.cpp"
        "Engine Systems/Managers/Menu_Manager.h"

)