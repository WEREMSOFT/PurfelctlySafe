//
// Created by Pablo Weremczuk on 2019-05-01.
//

#pragma once
#include "../animation.hpp"
#include "sprite_game_object.hpp"
#include <vector>

template <unsigned int animationNumber>
struct AnimatedGameObject: public GameObject {
    sf::Sprite* sprite;

    Animation animations[animationNumber];
    unsigned int currentAnimation;
    bool flipped = false;

    explicit AnimatedGameObject(){
    }

    void playAnimation(unsigned int animationId) {
        animations[animationId].playAnimation();
        sprite = &animations[animationId].sprite;
        currentAnimation = animationId;
    }

    void stopAnimation() {
        animations[currentAnimation].get()->stopAnimation();
    }

    void processAnimationFrame(const sf::Time& dt) {
        // This flips the sprite based on the "flipped" field.
        animations[currentAnimation].sprite.setScale(flipped ? -1.0 : 1.0, 1.0);
        animations[currentAnimation].processAnimationFrame(dt);
    }

protected:
    virtual void updateCurrent(const sf::Time dt) override {
        sprite = &animations[currentAnimation].sprite;
        processAnimationFrame(dt);
    }

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(animations[currentAnimation].sprite, states);
    }

};


