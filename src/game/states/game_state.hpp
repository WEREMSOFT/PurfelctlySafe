//
// Created by Pablo Weremczuk on 2019-04-22.
//

#pragma once


#include "../../core/states/state.hpp"

struct GameState: public State {
    FPSCounter fpsCounter;
    GameState(StateStack& stateStack, Context& context):
    State(stateStack, context),
    world(context),
    inputHandler(*context.inputHandler){
        fpsCounter.text.setFont(context.fontHolder->get(Fonts::PRESS_START));
    }

    ~GameState(){
        std::cout << "destruyendo game" << std::endl;
    }

    GameState(const GameState& other) = delete;

    bool update(sf::Time dt) override {
        world.update(dt);
        fpsCounter.update(dt);
        CommandQueue& commands = world.getCommandQueue();
        return false;
    }

    void draw() override {
        world.draw();
        context.window->draw(fpsCounter);
    }

    bool handleEvent(sf::Event event) override {
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::BackSpace){
                stack.popState();
            }
        }
        return false;
    }

    World world;
    InputHandler& inputHandler;
};


