#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"
#include "../core/context.hpp"
#include "../core/states/state_stack.hpp"
#include "states.hpp"
#include "states/title_state.hpp"
#include "states/menu_state.hpp"
#include "states/pause_state.hpp"
#include "states/game_state.hpp"
#include "states/loading_state.hpp"

#define SCREEN_WIDTH 1230
#define SCREEN_HEIGHT 768

struct Application {
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::RenderWindow window;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    InputHandler inputHandler;
    Context context;
    StateStack stateStack;
    // Scaling objects
    sf::RenderTexture renderTexture;
    sf::View view;

    Application() :
            window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Apllication", sf::Style::Default),
            textureHolder(),
            fontHolder(),
            inputHandler(),
            context(window, textureHolder, fontHolder, inputHandler),
            stateStack(context) {

        std::cout << "creating application..." << std::endl;

        renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

        // This scales the fullscreen to match the screen resolution of the target.
//        view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        view.setSize(window.getSize().x, window.getSize().y);
        view.setCenter(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        window.setView(view);

        stateStack.registerState<LoadingState>(States::LOADING);
        stateStack.registerState<GameState>(States::GAME);
        stateStack.registerState<TitleState>(States::TITLE);

        stateStack.pushState(States::LOADING);
    }

    ~Application() {
        std::cout << "destroying application" << std::endl;
    }

    void run() {

        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (window.isOpen()) {
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                processInput();
                update(TimePerFrame);
            }
            render();
        }
    }

    void update(sf::Time deltaTime) {
        stateStack.update(deltaTime);
        if(stateStack.isEmpty()) window.close();
    }

    void render() {
        window.clear();
        stateStack.draw();
//        window.setView(window.getDefaultView());
        window.display();
    }

    void processInput() {
        sf::Event event;
        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }

            inputHandler.processEvent(event);
            stateStack.handleEvent(event);
        }


    }
};