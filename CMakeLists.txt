cmake_minimum_required(VERSION 3.13)
project(PurfectlySafe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++17-extensions -framework GLUT -framework sfml-audio  -framework sfml-graphics -framework sfml-window -framework sfml-system")
file(COPY assets DESTINATION ./)


add_executable(PurfectlySafe src/main.cpp src/core/entity/game_object.hpp src/core/entity/sprite_game_object.hpp src/core/resources/resource_holder.hpp src/game/resource_definitions.hpp src/game/application.hpp src/game/world.hpp src/core/command/command.hpp)