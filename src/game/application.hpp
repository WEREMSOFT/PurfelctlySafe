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

struct Application {
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::RenderWindow window;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    InputHandler inputHandler;
    Context context;
//    World world;
    StateStack stateStack;

    Application() :
            window(sf::VideoMode(1230, 768), "SFML Apllication"),
            textureHolder(),
            fontHolder(),
            inputHandler(),
            context(window, textureHolder, fontHolder, inputHandler),
            stateStack(context) {
        std::cout << "creating application..." << std::endl;
        loadTextures();
        stateStack.registerState<GameState>(States::GAME);
        stateStack.pushState(States::GAME);
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
    }

    void loadTextures() {
        context.textureHolder->load(Textures::BACKGROUND, "./assets/images/background.jpg");
        context.textureHolder->load(Textures::LIGHT_O_TABLE, "./assets/images/light-o-table.png");
        context.textureHolder->load(Textures::TABLE, "./assets/images/table.png");
        context.textureHolder->load(Textures::HOUSE, "./assets/images/house.png");
        context.textureHolder->load(Textures::TITLE_BACKGROUND_TILE, "../assets/images/pattern_background.png");
    }

    void render() {
        window.clear();
        stateStack.draw();
        window.setView(window.getDefaultView());
        window.display();
    }

    void processInput() {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

        inputHandler.processEvent(event);
        stateStack.handleEvent(event);
    }

    void registerStates(){
//        stateStack.registerState<TitleState>(States::TITLE);
//        stateStack.registerState<Menu>(States::MENU);
//        stateStack.registerState<Pause>(States::PAUSE);
        stateStack.registerState<GameState>(States::GAME);
    }
};