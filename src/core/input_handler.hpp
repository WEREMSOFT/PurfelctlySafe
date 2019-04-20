//
// Created by Pablo Weremczuk on 2019-04-19.
//

#pragma once
#include <map>
#include "command/command_queue.hpp"
#include <functional>

struct InputHandler {
    float playerSpeed = 50.f;
    enum Action
    {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        PRINT_POSITION,
        ACTIONCOUNT
    };

    std::map<sf::Keyboard::Key, Action>		keyBinding;
    std::map<Action, Command>				actionBinding;

    InputHandler(){

        // Set initial key bindings
        keyBinding[sf::Keyboard::Left] = MOVE_LEFT;
        keyBinding[sf::Keyboard::Right] = MOVE_RIGHT;
        keyBinding[sf::Keyboard::Up] = MOVE_UP;
        keyBinding[sf::Keyboard::Down] = MOVE_DOWN;
        keyBinding[sf::Keyboard::Space] = PRINT_POSITION;

        initializeActions();



    }

    void initializeActions()
    {
        const float playerSpeed = 200.f;
        Command cmd;

        auto myCommandAction = [playerSpeed] (sf::Vector2f direction, GameObject& go, sf::Time dt) {
            go.move(direction * playerSpeed * dt.asSeconds());
        };

        cmd.category = Category::TABLE;

        cmd.action = std::bind(myCommandAction, sf::Vector2f(-1.f, 0), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_LEFT] = std::move(cmd);

        cmd.action = std::bind(myCommandAction, sf::Vector2f(1.f, 0), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_RIGHT] = std::move(cmd);

        cmd.action = std::bind(myCommandAction, sf::Vector2f(0, -1.f), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_UP] = std::move(cmd);

        cmd.action = std::bind(myCommandAction, sf::Vector2f(0, 1.f), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_DOWN] = std::move(cmd);

        cmd.action = [](GameObject& go, sf::Time dt) {
            std::cout << go.getPosition().x << " - " << go.getPosition().y << std::endl;
        };

        cmd.category = Category::TABLE;
        actionBinding[PRINT_POSITION] = std::move(cmd);
    }

    void handleRealtimeInput(CommandQueue& commands)
    {
        // Traverse all assigned keys and check if they are pressed
        for(auto pair: keyBinding)
        {
            // If key is pressed, lookup action and trigger corresponding command
            if (sf::Keyboard::isKeyPressed(pair.first))
                commands.push(actionBinding[pair.second]);
        }
    }

};
