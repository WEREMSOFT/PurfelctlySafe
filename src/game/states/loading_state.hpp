//
// Created by Pablo Weremczuk on 2019-04-27.
//

#pragma once

#include <thread>
#include <functional>

#include "../../core/states/state.hpp"
#include "../resource_definitions.hpp"
#include "../../core/utils.hpp"

struct LoadingState : public State {

    bool finished = false;
    int resourceConunter = 0;
    std::mutex lockScopeHandler;
    std::vector<std::thread> threads;
    sf::Text loadingText;
    sf::RectangleShape progressBarBackgroud;
    sf::RectangleShape progressBar;
    float percentajeLoaded = 0.f;

    std::function<void (Textures::ID id, const std::string &filename)> loadTexture = [&](Textures::ID id, const std::string &filename) -> void {
        lockScopeHandler.lock();
        resourceConunter++;
        lockScopeHandler.unlock();


        context.textureHolder->load(id, filename);

        lockScopeHandler.lock();
        resourceConunter--;
        lockScopeHandler.unlock();
    };

    LoadingState(StateStack &stateStack, Context &context) : State(stateStack, context) {

        threads.reserve(Textures::TEXTURE_COUNT);

        showIndicators();

        threads.emplace_back(loadTexture, Textures::BACKGROUND, "./assets/images/background.jpg");
        threads.emplace_back(loadTexture, Textures::LIGHT_O_TABLE, "./assets/images/light-o-table.png");
        threads.emplace_back(loadTexture, Textures::TABLE, "./assets/images/table.png");
        threads.emplace_back(loadTexture, Textures::HOUSE, "./assets/images/house.png");
        threads.emplace_back(loadTexture, Textures::TITLE_BACKGROUND_TILE, "../assets/images/pattern_background.png");
        threads.emplace_back(loadTexture, Textures::TITLE_MAIN_IMAGE, "../assets/images/title.png");
        threads.emplace_back(loadTexture, Textures::CAT_1_ANIMATION, "../assets/images/characters/cat1.png");


        std::cout << "...assets loaded" << std::endl;
    }

    void showIndicators() {
        std::cout << "Loading assets..." << std::endl;
        context.fontHolder->load(Fonts::PRESS_START, "../assets/fonts/PressStart2P-Regular.ttf");

        loadingText.setFont(context.fontHolder->get(Fonts::PRESS_START));
        loadingText.setString("Loading Resources");
        centerOrigin(loadingText);

        centerOnScreen(loadingText, *context.window);

        progressBarBackgroud.setFillColor(sf::Color::White);
        progressBarBackgroud.setSize(sf::Vector2f(context.window->getSize().x - 20, 40.f));
        progressBarBackgroud.setPosition(15, loadingText.getPosition().y + 40);

        progressBar.setFillColor(sf::Color::Red);
        progressBar.setSize(sf::Vector2f(200, 30));
        progressBar.setPosition(20, loadingText.getPosition().y + 45);
    }

    LoadingState(const LoadingState &other) = delete;

    void draw() override {
        context.window->draw(loadingText);
        context.window->draw(progressBarBackgroud);
        context.window->draw(progressBar);
    }

    bool update(sf::Time dt) override {
        percentajeLoaded = (float) resourceConunter / (float) Textures::TEXTURE_COUNT;
        auto substraction = context.window->getSize().x * percentajeLoaded + 30;
        progressBar.setSize(sf::Vector2f( context.window->getSize().x - substraction, 30));

        if (resourceConunter != 0) {
            percentajeLoaded = (float) resourceConunter / (float) Textures::TEXTURE_COUNT * 100.0f;
        }
        else {
            for (int i = 0; i < Textures::TEXTURE_COUNT; i++) {
                if(threads[i].joinable())threads[i].join();
            }
        }

        return false;
    }

    bool handleEvent(sf::Event event) override {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                stack.popState();
                stack.pushState(States::TITLE);
            }
        }
        return true;
    }

    ~LoadingState() {
        std::cout << "Destroying loading state" << std::endl;
    }
};


