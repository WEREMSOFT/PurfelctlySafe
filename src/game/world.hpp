#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "../core/entity/game_object.hpp"
#include "../core/entity/sprite_game_object.hpp"
#include "category.hpp"
#include "input_handler.hpp"
#include "../core/context.hpp"
#include "../core/entity/animated_game_object.hpp"
#include "characters/cat.hpp"

struct World: sf::NonCopyable {

    explicit World(Context& context):
    window(*context.window),
    view(window.getDefaultView()),
    context(context) {
        buildScene();
    }

    ~World(){
        std::cout << "destroying world" << std::endl;
    }

    World(const World& other) = delete;

    void buildScene(){
        for(std::size_t i = 0; i < LAYER_COUNT; ++i){
            GameObject::Ptr layer(new GameObject());
            sceneLayers[i] = layer.get();
            scene.addChild(std::move(layer));
        }

        GameObject::Ptr background(new SpriteGameObject(context.textureHolder->get(Textures::BACKGROUND)));
        background.get()->category = Category::BACKGROUND;
        GameObject::Ptr house(new SpriteGameObject(context.textureHolder->get(Textures::HOUSE)));
        GameObject::Ptr table(new SpriteGameObject(context.textureHolder->get(Textures::TABLE)));
        table.get()->category = Category::TABLE;
        table.get()->setPosition(519.f, 436.f);

        GameObject::Ptr cat(new Cat(context));
        cat.get()->setPosition(349, 260);


        GameObject::Ptr lightOfTable(new SpriteGameObject(context.textureHolder->get(Textures::LIGHT_O_TABLE)));

        table.get()->addChild(std::move(lightOfTable));

        sceneLayers[BACKGROUND]->addChild(std::move(background));
        sceneLayers[MIDDLE]->addChild(std::move(house));
        sceneLayers[FOREGROUND]->addChild(std::move(table));
        sceneLayers[FOREGROUND]->addChild(std::move(cat));
    }

    void update(sf::Time dt) {
        context.inputHandler->handleRealtimeInput(commandQueue);

        while(!commandQueue.isEmpty())
            scene.onCommand(commandQueue.pop(), dt);

        scene.update(dt);
    }

    void draw() {
        window.setView(view);
        window.draw(scene);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            window.draw(sf::Sprite(context.textureHolder->get(Textures::CAT_1_ANIMATION)));
        }
    }

    CommandQueue& getCommandQueue() {
        return commandQueue;
    }

private:
    sf::RenderWindow& window;
    sf::View view;
    GameObject scene;
    enum Layers {
        BACKGROUND,
        MIDDLE,
        FOREGROUND,
        LAYER_COUNT
    };
    std::array<GameObject*, LAYER_COUNT> sceneLayers;
    CommandQueue commandQueue;
    Context& context;
};
