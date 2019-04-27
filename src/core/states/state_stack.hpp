//
// Created by Pablo Weremczuk on 2019-04-21.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "../context.hpp"
#include "state.hpp"

struct StateStack : private sf::NonCopyable {
    enum Action {
        PUSH,
        POP,
        CLEAR
    };

    struct PendingChange {
        explicit PendingChange(Action action, int stateID = 0): action(action), stateID(stateID) {}
        Action action;
        int stateID;
    };

    explicit StateStack(Context& context): context(context) {

    }

    StateStack(const StateStack& other) = delete;

    template<typename T>
    void registerState(int stateID) {
        factories[stateID] = [this] () {
            return State::Ptr(new T(*this, context));
        };
    }

    void update(sf::Time dt) {
        for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr){
            if(!(*itr)->update(dt)) break;
        }
        applyPendingChanges();
    }

    void draw() {
        for(State::Ptr& state: stack){
            state->draw();
        }
    }

    void handleEvent(const sf::Event &event) {
        for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr){
            if(!(*itr)->handleEvent(event)) return;
        }
    }

    void pushState(int stateID) {
        pendingList.push_back(PendingChange(PUSH, stateID));
    }

    void popState() {
        pendingList.push_back(PendingChange(POP));
    }

    void clearStates() {
        stack.clear();
    }

    bool isEmpty() const {
        return stack.empty();
    };

    State::Ptr createState(int stateID){
        auto found = factories.find(stateID);
        assert(found != factories.end());
        return found->second();
    }
    void applyPendingChanges(){
        for(PendingChange change: pendingList){
            switch(change.action){
                case PUSH:
                    stack.push_back(createState(change.stateID));
                    break;
                case POP:
                    stack.pop_back();
                    break;
                case CLEAR:
                    stack.clear();
                    break;
            }
        }

        pendingList.clear();
    }

private:
    std::vector<State::Ptr> stack;
    std::vector<PendingChange> pendingList;
    Context& context;
    std::map<int, std::function<State::Ptr()>> factories;
};


