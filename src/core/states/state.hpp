//
// Created by Pablo Weremczuk on 2019-04-22.
//

#pragma once
#include <memory>
#include "../context.hpp"
#include "state_stack.hpp"
struct StateStack;

struct State {
    typedef std::unique_ptr<State> Ptr;

    State(StateStack& stack, Context context): context(context), stack(stack)
    {
    }

    virtual ~State(){}

    virtual void draw(){}
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(sf::Event event) = 0;

protected:
    void requestStackPush(int stateID){}
    void requestStackPop(){}
    void requestStackClear();

private:
    StateStack& stack;
    Context context;
};


