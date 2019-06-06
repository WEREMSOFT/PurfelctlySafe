cmake_minimum_required(VERSION 3.7.2)
project(PurfectlySafe)

set(OPTIMIZATION_FLAGS "-O3")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -Wc++17-extensions -framework GLUT -framework sfml-audio  -framework sfml-graphics -framework sfml-window -framework sfml-system")
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -std=c++11 -I/home/pi/documents/sfml-pi/include -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread")
endif()
file(COPY assets DESTINATION ./)


add_executable(PurfectlySafe src/main.cpp src/core/animation.hpp src/core/entity/game_object.hpp src/core/entity/sprite_game_object.hpp src/core/resources/resource_holder.hpp src/game/resource_definitions.hpp src/game/application.hpp src/game/world.hpp src/core/command/command.hpp src/core/states/state_stack.hpp src/core/states/state.hpp src/game/states.hpp src/game/states/title_state.hpp src/game/states/menu_state.hpp src/game/states/game_state.hpp src/game/states/pause_state.hpp src/game/states/loading_state.hpp src/core/utils.hpp src/core/entity/animated_game_object.hpp src/game/characters/cat.hpp src/game/characters/cat_commands.hpp src/game/characters/cat_states.hpp src/core/debug/fps_counter.hpp src/game/characters/cat_2.hpp)