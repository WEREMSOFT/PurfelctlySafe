//
// Created by Pablo Weremczuk on 2019-04-27.
//

#pragma once
#include <thread>
#include <functional>

#include "../../core/states/state.hpp"
#include "../resource_definitions.hpp"

struct LoadingState : public State {

    bool finished = false;
    int textureConunter = 0;
    std::mutex lockScopeHandler;
    std::thread threads[Textures::TEXTURE_COUNT];

    LoadingState(StateStack &stateStack, Context &context) : State(stateStack, context) {


        auto loadTexture = [&] (Textures::ID id, const std::string &filename) -> void {
            lockScopeHandler.lock();
            textureConunter++;
            lockScopeHandler.unlock();


            context.textureHolder->load(id, filename);

            lockScopeHandler.lock();
            textureConunter--;
            lockScopeHandler.unlock();
            std::cout << "joining thread " << std::this_thread::get_id() << std::endl;
        };

        std::cout << "Loading assets..." << std::endl;

        threads[Textures::BACKGROUND] = std::thread(loadTexture, Textures::BACKGROUND, "./assets/images/background.jpg");
        threads[Textures::LIGHT_O_TABLE] = std::thread(loadTexture, Textures::LIGHT_O_TABLE, "./assets/images/light-o-table.png");
        threads[Textures::TABLE] = std::thread(loadTexture, Textures::TABLE, "./assets/images/table.png");
        threads[Textures::HOUSE] = std::thread(loadTexture, Textures::HOUSE, "./assets/images/house.png");
        threads[Textures::TITLE_BACKGROUND_TILE] = std::thread(loadTexture, Textures::TITLE_BACKGROUND_TILE, "../assets/images/pattern_background.png");

        float percentajeLoaded = 0.f;

        while(textureConunter != 0){
            percentajeLoaded = (float)textureConunter / (float)Textures::TEXTURE_COUNT * 100.0f;
            std::cout << "textures remaining " << percentajeLoaded << "%" << std::endl;
        }

        for(int i; i < Textures::TEXTURE_COUNT; i++){
            threads[i].join();
        }

        std::cout << "...assets loaded" << std::endl;
    }

    LoadingState(const LoadingState& other) = delete;

    void draw() override {
    }

    bool update(sf::Time dt) override {
        stack.popState();
        stack.pushState(States::TITLE);
        return false;
    }

    bool handleEvent(sf::Event event) override {
        return true;
    }

    ~LoadingState(){
        std::cout << "Destroying loading state" << std::endl;
    }
};


