cmake_minimum_required(VERSION 3.29.1)

project(SFMLEIG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

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
        "Engine Systems/Managers/Object_Manager.cpp"
        "Engine Systems/Managers/Object_Manager.h"

)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SFML::Graphics)



