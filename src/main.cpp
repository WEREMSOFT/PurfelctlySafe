#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/entity/game_object.hpp"
#include "game/resource_definitions.hpp"
#include "game/application.hpp"

int main() {
    std::cout << "Startign game..." << std::endl;

    Application application;
    application.run();

    return 0;
}