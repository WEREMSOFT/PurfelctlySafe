//
// Created by Pablo Weremczuk on 2019-05-01.
//

#pragma once


#include "../../core/entity/animated_game_object.hpp"
#include "../../core/context.hpp"
#include "../resource_definitions.hpp"
#include <memory>
#include <functional>

enum CatAnimations {
    ANIM_IDLE,
    ANIM_RUNNING,
    ANIM_AMMOUNT
};

struct Cat: public AnimatedGameObject<ANIM_AMMOUNT>  {
    sf::Vector2f lastPosition;

    explicit Cat(Context& context){
        category = Category::CAT_1;
        animations[CatAnimations::ANIM_IDLE].setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));
        animations[CatAnimations::ANIM_IDLE].maxFrames = 5;
        animations[CatAnimations::ANIM_IDLE].frameSize =  {0, 26, 135, 154};
        animations[CatAnimations::ANIM_IDLE].framesPerSeccond = 10;
        animations[CatAnimations::ANIM_IDLE].setCentered(true);

        animations[CatAnimations::ANIM_RUNNING].setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));
        animations[CatAnimations::ANIM_RUNNING].maxFrames = 8;
        animations[CatAnimations::ANIM_RUNNING].frameSize =  {0, 767, 148, 193};
        animations[CatAnimations::ANIM_RUNNING].framesPerSeccond = 8;
        animations[CatAnimations::ANIM_RUNNING].setCentered(true);

        playAnimation(CatAnimations::ANIM_IDLE);
    }

protected:
    virtual void updateCurrent(sf::Time dt) override {
        AnimatedGameObject::updateCurrent(dt);
        if(lastPosition.x == getPosition().x && lastPosition.y == getPosition().y){
            playAnimation(CatAnimations::ANIM_IDLE);
        }

        lastPosition.x = getPosition().x;
        lastPosition.y = getPosition().y;
    }

};


