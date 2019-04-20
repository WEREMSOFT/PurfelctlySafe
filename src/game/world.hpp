#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../core/entity/game_object.hpp"
#include "../core/entity/sprite_game_object.hpp"
#include "category.hpp"
#include "../core/input_handler.hpp"
#include "../core/context.hpp"

struct World: sf::NonCopyable {


    explicit World(sf::RenderWindow& pWindow):
    window(pWindow),
    view(window.getDefaultView()) {
        loadTextures();
        buildScene();
    }

    ~World(){
        std::cout << "destroying world" << std::endl;
    }

    void buildScene(){
        for(std::size_t i = 0; i < LAYER_COUNT; ++i){
            GameObject::Ptr layer(new GameObject());
            sceneLayers[i] = layer.get();
            scene.addChild(std::move(layer));
        }


        GameObject::Ptr background(new SpriteGameObject(textures.get(Textures::BACKGROUND)));
        background.get()->category = Category::BACKGROUND;
        GameObject::Ptr house(new SpriteGameObject(textures.get(Textures::HOUSE)));
        GameObject::Ptr table(new SpriteGameObject(textures.get(Textures::TABLE)));
        table.get()->category = Category::TABLE;
        table.get()->setPosition(519.f, 436.f);

        sceneLayers[BACKGROUND]->addChild(std::move(background));
        sceneLayers[MIDDLE]->addChild(std::move(house));
        sceneLayers[FOREGROUND]->addChild(std::move(table));
    }

    void update(sf::Time dt) {
        inputHandler.handleRealtimeInput(commandQueue);

        while(!commandQueue.isEmpty())
            scene.onCommand(commandQueue.pop(), dt);

        scene.update(dt);
    }

    void draw() {
        window.setView(view);
        window.draw(scene);
    }

    void loadTextures() {
        textures.load(Textures::BACKGROUND, "./assets/images/background.jpg");
        textures.load(Textures::TABLE, "./assets/images/table.png");
        textures.load(Textures::HOUSE, "./assets/images/house.png");
    }

private:
    sf::RenderWindow& window;
    sf::View view;
    GameObject scene;
    TextureHolder textures;
    enum Layers {
        BACKGROUND,
        MIDDLE,
        FOREGROUND,
        LAYER_COUNT
    };
    std::array<GameObject*, LAYER_COUNT> sceneLayers;
    InputHandler inputHandler;
    CommandQueue commandQueue;
};