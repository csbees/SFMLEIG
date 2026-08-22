cmake_minimum_required(VERSION 3.29.1)

project(SFMLEIG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)


FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.9b
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO OFF)

FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG master
)

FetchContent_MakeAvailable(imgui-sfml)

add_executable(
        ${CMAKE_PROJECT_NAME}
        Scripts/main.cpp
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
        "Engine Systems/Managers/Object_Manager.cpp"
        "Engine Systems/Managers/Object_Manager.h"
        "Game Objects/Asteroids_Game.cpp"
        "Game Objects/Asteroids_Game.h"
        "Engine Systems/Managers/Music_Manager.cpp"
        "Engine Systems/Managers/Music_Manager.h"
        "Game Objects/Player.cpp"
        "Game Objects/Player.h"
        "Game Objects/Asteroid.cpp"
        "Game Objects/Asteroid.h"
        "Game Objects/Bullet.cpp"
        "Game Objects/Bullet.h"
        "Game Objects/Asteroid_Manager.cpp"
        "Game Objects/Asteroid_Manager.h"
        "Engine Systems/Physics_node.h"
        "Engine Systems/Physics_node.h"
        "Engine Systems/sound_container.h"

)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
            SFML::Graphics
            SFML::Audio
            ImGui-SFML::ImGui-SFML
)



