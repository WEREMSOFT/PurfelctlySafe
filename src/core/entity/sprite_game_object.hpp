#pragma once

#include "game_object.hpp"

struct SpriteGameObject: public GameObject {
    sf::Sprite sprite;
    explicit SpriteGameObject(const sf::Texture &texture): sprite(texture){
    }

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }
};