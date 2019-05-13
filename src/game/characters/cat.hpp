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

struct Cat: public AnimatedGameObject<ANIM_AMMOUNT>  {
    sf::Vector2f lastPosition;
    int state = CatStates::STATE_IDLE;

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

        playAnimation(CatAnimations::ANIM_IDLE);
    }


    void passToStateIdle(){
        state = CatStates::STATE_IDLE;
        playAnimation(CatAnimations::ANIM_IDLE);
    }


    void passToStateRunning(){
        state = CatStates::STATE_RUNNING;
        playAnimation(CatAnimations::ANIM_RUNNING);
    }

    void passToStateAttacking(){
        state = CatStates::STATE_ATTACKING;
        playAnimation(CatAnimations::ANIM_ATTACKING);
    }

    void processStateAttacking(){
        if(animations[currentAnimation].state == AnimationState::STOPED){
            passToStateIdle();
        }
    }

    void processStateRun() {
        if (lastPosition.x == getPosition().x && lastPosition.y == getPosition().y) {
            playAnimation(ANIM_IDLE);
            passToStateIdle();
        }
        restrictMovementToRoom();
    }

    void restrictMovementToRoom() {
        auto position = getPosition();
        position.y = std::min(542.0f, std::max(250.0f, position.y));
        position.x = std::min(750.0f + position.y * 0.3f, std::max(460.0f - position.y * 0.3f, position.x));

        setPosition(position);
    }
protected:
    virtual void updateCurrent(sf::Time dt) override {

        switch (state){
            case CatStates::STATE_IDLE:
                break;
            case CatStates::STATE_RUNNING:
                processStateRun();
                break;
            case CatStates ::STATE_ATTACKING:
                processStateAttacking();
        }

        lastPosition.x = getPosition().x;
        lastPosition.y = getPosition().y;

        AnimatedGameObject::updateCurrent(dt);
    }

};
//
//void processStateRun(Cat &cat, sf::Time dt) {
//    if (cat.lastPosition.x == cat.getPosition().x && cat.lastPosition.y == cat.getPosition().y) {
//        cat.playAnimation(ANIM_IDLE);
//        cat.stateStack.pop_back();
//    }
//}
//
//void processStateAttack(Cat &cat, sf::Time sf){
//    if(cat.animations[cat.currentAnimation].state == AnimationState::STOPED){
//        cat.stateStack.pop_back();
//    }
//}
//
//void processStateIdle(Cat &cat, sf::Time sf) {
//    cat.playAnimation(CatAnimations::ANIM_IDLE);
//    if (cat.lastPosition.x != cat.getPosition().x || cat.lastPosition.y != cat.getPosition().y){
//        cat.stateStack.push_back(processStateRun);
//    }
//}
