#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/entity/game_object.hpp"
#include "game/resource_definitions.hpp"
#include "game/game.hpp"

int main() {
    std::cout << "Startign game..." << std::endl;

    Game game;
    game.run();

    return 0;
}