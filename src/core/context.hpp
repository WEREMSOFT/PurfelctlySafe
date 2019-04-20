//
// Created by Pablo Weremczuk on 2019-04-20.
//

#pragma once
#include "./resources/resource_holder.hpp"
#include "input_handler.hpp"

struct Context {
    Context(sf::RenderWindow& pWindow,
            TextureHolder& pTextureHolder,
            FontHolder& pFontHolder,
            InputHandler& pInputHandler):
            window(&pWindow),
            textureHolder(&pTextureHolder),
            fontHolder(&pFontHolder),
            inputHandler(&pInputHandler){}
    sf::RenderWindow* window;
    TextureHolder* textureHolder;
    FontHolder* fontHolder;
    InputHandler* inputHandler;
    ~Context(){
        std::cout << "destroying context" << std::endl;
    }
};


