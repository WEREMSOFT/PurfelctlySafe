//
// Created by Pablo Weremczuk on 2019-04-20.
//

#pragma once
#include "./resources/resource_holder.hpp"
#include "input_handler.hpp"

struct Context {
    Context(sf::RenderWindow& window,
            TextureHolder& textureHolder,
            FontHolder& fontHolder,
            InputHandler& inputHandler):
            window(&window),
            textureHolder(&textureHolder),
            fontHolder(&fontHolder),
            inputHandler(&inputHandler){}
    sf::RenderWindow* window;
    TextureHolder* textureHolder;
    FontHolder* fontHolder;
    InputHandler* inputHandler;
    ~Context(){
        std::cout << "destroying context" << std::endl;
    }
};


