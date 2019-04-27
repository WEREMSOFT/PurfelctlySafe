//
// Created by Pablo Weremczuk on 2019-04-22.
//

#pragma once


#include "../../core/states/state.hpp"

struct TitleState : public State {
    sf::Sprite backgroundSprite;

    TitleState(StateStack &stateStack, Context& context) :
            State(stateStack, context){
        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        backgroundSprite.setTexture(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, context.window->getSize().x, context.window->getSize().y));
    }

    TitleState(const TitleState& other) = delete;

    void draw() override {
        context.window->draw(backgroundSprite);
    }

    bool update(sf::Time dt) override {
        return true;
    }

    bool handleEvent(sf::Event event) override {
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Space){
                stack.pushState(States::GAME);
            }
        }

        return true;
    }

};


