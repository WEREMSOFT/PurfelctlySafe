//
// Created by Pablo Weremczuk on 2019-04-27.
//

#pragma once
#include <SFML/Graphics.hpp>

void centerOrigin(sf::Text &sprite) {
    sf::FloatRect bounds{sprite.getLocalBounds()};
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void centerOnScreen(sf::Text &text, sf::RenderWindow& window){
    text.setPosition(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u);
}