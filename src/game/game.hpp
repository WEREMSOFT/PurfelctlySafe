#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"
#include "../core/context.hpp"

struct Game{
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    Game():
    window(sf::VideoMode(1230, 768), "SFML Apllication"),
    textureHolder(),
    fontHolder(),
    inputHandler(),
    context(window, textureHolder, fontHolder, inputHandler), world(window) {
        std::cout << "creating game..." << std::endl;
    }

    ~Game(){
        std::cout << "destroying game" << std::endl;
    }

    void run() {

        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while(window.isOpen()) {
            timeSinceLastUpdate += clock.restart();
            while(timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                processInput();
                update(TimePerFrame);
            }
            render();
        }
    }

    void update(sf::Time deltaTime) {
        world.update(deltaTime);
    }


    void render() {
        window.clear();
        world.draw();
        window.setView(window.getDefaultView());
        window.display();
    }

    void processInput() {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

    }
    sf::RenderWindow window;
    World world;
    Context context;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    InputHandler inputHandler;
};