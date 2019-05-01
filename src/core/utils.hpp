//
// Created by Pablo Weremczuk on 2019-04-27.
//

#pragma once
#include <SFML/Graphics.hpp>

void centerOrigin(sf::Text &sprite) {
    sf::FloatRect bounds{sprite.getLocalBounds()};
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void centerOnScreen(sf::Text &text, sf::Window& window){
    text.setPosition(window.getSize().x / 2u, window.getSize().y / 2u);
}