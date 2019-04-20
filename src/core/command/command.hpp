#pragma once
struct GameObject;
#include "../entity/game_object.hpp"
#include <functional>

struct Command {
    std::function<void(GameObject&, sf::Time)> action;
    int category = 0;
};