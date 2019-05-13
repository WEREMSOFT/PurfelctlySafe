//
// Created by Pablo Weremczuk on 2019-05-12.
//

#pragma once

#import "cat.hpp"
#import "../category.hpp"

struct Cat2: public Cat {

    explicit Cat2(Context& context): Cat(context){
        category = Category::CAT_1;
        animations[CatAnimations::ANIM_IDLE].setTexture(context.textureHolder->get(Textures::CAT_2_ANIMATION));
        animations[CatAnimations::ANIM_IDLE].maxFrames = 1;
        animations[CatAnimations::ANIM_IDLE].frameSize =  {34, 28, 148, 141};
        animations[CatAnimations::ANIM_IDLE].framesPerSeccond = 1;
        animations[CatAnimations::ANIM_IDLE].setCentered(true);

        animations[CatAnimations::ANIM_RUNNING].setTexture(context.textureHolder->get(Textures::CAT_2_ANIMATION));
        animations[CatAnimations::ANIM_RUNNING].maxFrames = 8;
        animations[CatAnimations::ANIM_RUNNING].frameSize =  {33, 738, 149, 193};
        animations[CatAnimations::ANIM_RUNNING].framesPerSeccond = 8;
        animations[CatAnimations::ANIM_RUNNING].setCentered(true);

        animations[CatAnimations::ANIM_ATTACKING].setTexture(context.textureHolder->get(Textures::CAT_2_ANIMATION));
        animations[CatAnimations::ANIM_ATTACKING].maxFrames = 5;
        animations[CatAnimations::ANIM_ATTACKING].frameSize =  {0, 330, 148, 144};
        animations[CatAnimations::ANIM_ATTACKING].framesPerSeccond = 15;
        animations[CatAnimations::ANIM_ATTACKING].looped = false;
        animations[CatAnimations::ANIM_ATTACKING].setCentered(true);
//
//        animations.emplace(std::make_pair(AnimationId::ANIM_CAT_2_WALKING, Animation(
//                textures[AssetId::CAT_2],
//                8,
//                {33, 738, 149, 193})));
//        animations[AnimationId::ANIM_CAT_2_WALKING].framesPerSeccond = 8;
//
//        animations.emplace(std::make_pair(AnimationId::ANIM_CAT_2_RUNNING, Animation(
//                textures[AssetId::CAT_2],
//                8,
//                {33, 738, 149, 193})));
//        animations[AnimationId::ANIM_CAT_2_RUNNING].framesPerSeccond = 8;
//
//        animations.emplace(std::make_pair(AnimationId::ANIM_CAT_2_IDLE, Animation(
//                textures[AssetId::CAT_2],
//                1,
//                {34, 28, 148, 141})));
//        animations[AnimationId::ANIM_CAT_2_IDLE].framesPerSeccond = 1;
//
//        animations.emplace(std::make_pair(AnimationId::ANIM_CAT_2_ATTACK, Animation(
//                textures[AssetId::CAT_2],
//                3,
//                {34, 336, 148, 141}, false)));
//        animations[AnimationId::ANIM_CAT_2_ATTACK].framesPerSeccond = 10;


        playAnimation(CatAnimations::ANIM_IDLE);
    }
};


