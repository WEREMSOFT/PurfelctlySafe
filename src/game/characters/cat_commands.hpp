#pragma once
#include <SFML/Graphics.hpp>

namespace commands{
    const float PLAYER_SPEED = 200.0f;

    void flipIfNecessary(sf::Vector2f& direction, GameObject& go){
        Cat& cat = ((Cat&) go);

        if(direction.x > 0){
            cat.flipped = true;
        } else if(direction.x < 0) {
            cat.flipped = false;
        }
    }

    void moveCat(sf::Vector2f direction, GameObject& go, sf::Time dt) {
        flipIfNecessary(direction, go);
        ((Cat&) go).playAnimation(CatAnimations::ANIM_RUNNING);
        go.move(direction * PLAYER_SPEED * dt.asSeconds());
    };

    void attackCat(sf::Vector2f direction, GameObject& go, sf::Time dt) {
        flipIfNecessary(direction, go);
        ((Cat&) go).playAnimation(CatAnimations::ANIM_ATTACKING);
    };

    void printPosition(GameObject& go, sf::Time dt) {
        std::cout << go.getPosition().x << " - " << go.getPosition().y << std::endl;
    }


}

