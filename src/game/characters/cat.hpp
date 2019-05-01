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
    ANIM_WALKING,
    ANIM_IDLE,
    ANIM_RUNNING,
    ANIM_ATTACK,
    ANIM_AMMOUNT
};

struct Cat: public AnimatedGameObject<ANIM_AMMOUNT>  {
    explicit Cat(Context& context){
        animations[CatAnimations::ANIM_IDLE].texture = &context.textureHolder->get(Textures::CAT_1_ANIMATION);
        animations[CatAnimations::ANIM_IDLE].maxFrames = 5;
        animations[CatAnimations::ANIM_IDLE].frameSize =  {0, 26, 135, 154};
        animations[CatAnimations::ANIM_IDLE].framesPerSeccond = 10;
        playAnimation(CatAnimations::ANIM_IDLE);
    }


};


