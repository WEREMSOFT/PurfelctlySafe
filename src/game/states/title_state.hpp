//
// Created by Pablo Weremczuk on 2019-04-22.
//

#pragma once


#include "../../core/states/state.hpp"
#include "../../core/utils.hpp"
#include "../../core/debug/fps_counter.hpp"

struct TitleState : public State {
    sf::Sprite backgroundSprite;
    sf::Sprite mainImage;
    sf::Text pressAnyKeyText;
    FPSCounter fpsCounter;

    TitleState(StateStack &stateStack, Context& context) :
            State(stateStack, context){
        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        backgroundSprite.setTexture(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, context.window->getSize().x, context.window->getSize().y));

        mainImage.setTexture(context.textureHolder->get(Textures::TITLE_MAIN_IMAGE));
        pressAnyKeyText.setFont(context.fontHolder->get(Fonts::PRESS_START));

        pressAnyKeyText.setString("Press Space To Start");
        pressAnyKeyText.setFillColor(sf::Color::White);
        centerOrigin(pressAnyKeyText);
        centerOnScreen(pressAnyKeyText, *context.window);
        pressAnyKeyText.move(0, 300);

        fpsCounter.text.setFont(context.fontHolder->get(Fonts::PRESS_START));

    }

    TitleState(const TitleState& other) = delete;

    void draw() override {
        context.window->draw(backgroundSprite);
        context.window->draw(mainImage);
        context.window->draw(pressAnyKeyText);
        context.window->draw(fpsCounter);
    }

    bool update(sf::Time dt) override {
        sf::IntRect rect = backgroundSprite.getTextureRect();
        rect.left += (100.f * dt.asSeconds());
        rect.top += (80.f * dt.asSeconds());
        backgroundSprite.setTextureRect(rect);
        fpsCounter.update(dt);

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


