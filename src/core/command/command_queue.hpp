//
// Created by Pablo Weremczuk on 2019-04-19.
//

#pragma once
#include <queue>
#include "command.hpp"

struct CommandQueue {
    void push(const Command& command){
        queue.push(command);
    }

    Command pop(){
        Command returnValue = queue.front();
        queue.pop();
        return returnValue;
    }

    bool isEmpty(){
        return queue.empty();
    }

    std::queue<Command> queue;
};


