//
// Created by Pablo Weremczuk on 2019-05-01.
//

#pragma once


#include "../../core/entity/animated_game_object.hpp"
#include "../../core/context.hpp"
#include "../resource_definitions.hpp"
#include "cat_states.hpp"
#include <memory>
#include <functional>

enum CatAnimations {
    ANIM_IDLE,
    ANIM_RUNNING,
    ANIM_ATTACKING,
    ANIM_AMMOUNT
};

struct Cat;
void processStateIdle(Cat &cat, sf::Time sf);

struct Cat: public AnimatedGameObject<ANIM_AMMOUNT>  {
    sf::Vector2f lastPosition;
    std::vector<std::function<void(Cat&, sf::Time)>> stateStack;

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

        animations[CatAnimations::ANIM_ATTACKING].setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));
        animations[CatAnimations::ANIM_ATTACKING].maxFrames = 5;
        animations[CatAnimations::ANIM_ATTACKING].frameSize =  {0, 330, 148, 144};
        animations[CatAnimations::ANIM_ATTACKING].framesPerSeccond = 15;
        animations[CatAnimations::ANIM_ATTACKING].looped = false;
        animations[CatAnimations::ANIM_ATTACKING].setCentered(true);

        stateStack.push_back(processStateIdle);

        playAnimation(CatAnimations::ANIM_IDLE);
    }

protected:
    virtual void updateCurrent(sf::Time dt) override {

        if(!stateStack.empty()){
            stateStack.back()(*this, dt);
        }

        lastPosition.x = getPosition().x;
        lastPosition.y = getPosition().y;

        AnimatedGameObject::updateCurrent(dt);
    }

};

void processStateRun(Cat &cat, sf::Time dt) {
    if (cat.lastPosition.x == cat.getPosition().x && cat.lastPosition.y == cat.getPosition().y) {
        cat.playAnimation(ANIM_IDLE);
        cat.stateStack.pop_back();
    }
}

void processStateAttack(Cat &cat, sf::Time sf){
    if(cat.animations[cat.currentAnimation].state == AnimationState::STOPED){
        cat.stateStack.pop_back();
    }
}

void processStateIdle(Cat &cat, sf::Time sf) {
    cat.playAnimation(CatAnimations::ANIM_IDLE);
    if (cat.lastPosition.x != cat.getPosition().x || cat.lastPosition.y != cat.getPosition().y){
        cat.stateStack.push_back(processStateRun);
    }
}
