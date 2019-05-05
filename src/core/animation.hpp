#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum AnimationState {
    PLAYING,
    STOPED
};

struct Animation {
    AnimationState state = AnimationState::STOPED;
    int maxFrames;
    float frame;
    int framesPerSeccond = 30;
    sf::Sprite sprite;
    sf::Rect<int> frameSize;
    bool looped = true;
    bool centered = false;

    Animation(){
        std::cout << "building animation " << std::endl;
        if(centered) {
            sprite.setOrigin(frameSize.width / 2, 0.0);
        } else {
            sprite.setOrigin(0.0, 0.0);
        }
    }

    ~Animation(){
        std::cout << "destroying animation " << std::endl;
    }

    Animation(sf::Texture& pTexture, int pMaxFrames, sf::Rect<int> pFrameSize, bool pLooped = true, bool pCentered = true) {
        centered = pCentered;
        frameSize = pFrameSize;
        maxFrames = pMaxFrames;
        setTexture(pTexture);
        sprite.setTextureRect(frameSize);
        if(centered) {
            sprite.setOrigin(frameSize.width / 2, 0.0);
        } else {
            sprite.setOrigin(0.0, 0.0);
        }
        looped = pLooped;
    }

    Animation(const Animation& other) = delete;
    Animation(const Animation&& other) = delete;

    void playAnimation() {
        state = AnimationState::PLAYING;
    }

    void stopAnimation() {
        state = AnimationState::STOPED;
    }

    void setTexture(sf::Texture& pTexture){
        sprite.setTexture(pTexture);
    }

    void processAnimationFrame(const sf::Time delta) {
        // only process animation if the animation is not stoped.
        if (state == AnimationState::PLAYING) {
            frame += framesPerSeccond * delta.asSeconds();
            if (frame > maxFrames) {
                frame = 0;
                if(!looped) {
                    stopAnimation();
                }
            }
        }

        gotoFrame(int(frame));
    }

    void gotoFrame(int frame){
        sprite.setTextureRect({
        frameSize.left + frameSize.width * frame,
        frameSize.top,
        frameSize.width,
        frameSize.height});
    }

    void gotoAndStop(int frame){
        stopAnimation();
        frame = (frame > maxFrames) ? maxFrames : frame;
        this->frame = frame;
        gotoFrame(frame);
    }
};

