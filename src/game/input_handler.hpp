//
// Created by Pablo Weremczuk on 2019-04-19.
//

#pragma once
#include <map>
#include "../core/command/command_queue.hpp"
#include "../core/entity/animated_game_object.hpp"
#include "characters/cat.hpp"
#include "characters/cat_commands.hpp"

#include <functional>

struct InputHandler {
    float playerSpeed = 50.f;
    enum Action
    {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        ATTACK,
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
        keyBinding[sf::Keyboard::P] = PRINT_POSITION;
        keyBinding[sf::Keyboard::Z] = ATTACK;

        initializeActions();
    }

    InputHandler(const InputHandler& other) = delete;

    void initializeActions()
    {
        Command cmd;

        cmd.category = Category::CAT_1;

        cmd.action = std::bind(commands::moveCat, sf::Vector2f(-1.f, 0), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_LEFT] = std::move(cmd);

        cmd.action = std::bind(commands::moveCat, sf::Vector2f(1.f, 0), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_RIGHT] = std::move(cmd);

        cmd.action = std::bind(commands::moveCat, sf::Vector2f(0, -1.f), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_UP] = std::move(cmd);

        cmd.action = std::bind(commands::moveCat, sf::Vector2f(0, 1.f), std::placeholders::_1, std::placeholders::_2);
        actionBinding[MOVE_DOWN] = std::move(cmd);

        cmd.action = std::bind(commands::attackCat, sf::Vector2f(0, 1.f), std::placeholders::_1, std::placeholders::_2);
        actionBinding[ATTACK] = std::move(cmd);

        cmd.action = commands::printPosition;

        cmd.category = Category::CAT_1;
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

    void processEvent(sf::Event event){
        if (event.type == sf::Event::KeyPressed){
//            std::cout << "Key pressed " << event.key.code << std::endl;
        }

    }

};
