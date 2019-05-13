//
// Created by Pablo Weremczuk on 2019-05-12.
//

#pragma once


#include "../entity/game_object.hpp"

struct FPSCounter : public GameObject {
    sf::Text text;
    sf::Clock clock;
    float lastTime = 0;
    std::map<int, int> registeredFPS;
    const int MAX_REGISTERED_FPS = 10;
    unsigned int registeredFPSIndex = 0;
    std::string label = "FPS: ";

    FPSCounter(){
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }

    explicit FPSCounter(const Context& context) {
        text.setFont(context.fontHolder->get(Fonts::PRESS_START));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }

    int calculateAVGFPS(){
        int acumulator = 0;
        for(auto i: registeredFPS){
            acumulator += i.second;
        }

        return acumulator / MAX_REGISTERED_FPS;
    }

protected:
    void updateCurrent(sf::Time dt) override {

        float currentTime = clock.restart().asSeconds();

        registeredFPS[registeredFPSIndex % MAX_REGISTERED_FPS] = (int)(1.f / (currentTime - lastTime));
        registeredFPSIndex++;


        text.setString(label + std::to_string((int)calculateAVGFPS()));

        lastTime = clock.restart().asSeconds();
    }

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(text, states);
    }
};
//    sf::Transform transform;
//    sf::Font* font;
//    sf::Clock clock;
//    int characterSize = 24;
//    sf::Color color = sf::Color::White;
//    float lastTime = 0;
//    std::map<int, int> registeredFPS;
//    const int MAX_REGISTERED_FPS = 10;
//    unsigned int registeredFPSIndex = 0;
//    std::string text = "FPS: ";
//
//    FPSCounter(){
//        lastTime = clock.restart().asSeconds();
//    }
//};


