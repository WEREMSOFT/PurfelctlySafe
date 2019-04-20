#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include "../command/command.hpp"

struct GameObject: public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
    typedef std::unique_ptr<GameObject> Ptr;
    int category = 0;

    void addChild(Ptr pChild) {
        pChild->parent = this;
        children.push_back(std::move(pChild));
    }

    GameObject* parent;
    std::vector<Ptr> children;

    void update(sf::Time dt) {
        updateCurrent(dt);
        updateChildren(dt);
    }

    Ptr removeChild(const GameObject &node) {
        auto found = std::find_if(
                children.begin(),
                children.end(),
                [&] (Ptr& p) -> bool {return p.get() == &node; });
        assert(found != children.end());
        Ptr result = std::move(*found);
        result->parent = nullptr;
        children.erase(found);
        return result;
    }

    void onCommand(const Command& command, sf::Time dt){
        if(category & command.category)
            command.action(*this, dt);

        for(GameObject::Ptr& child: children){
            child->onCommand(command, dt);
        }
    }


private:
    void updateCurrent(sf::Time dt){
    }

    void updateChildren(sf::Time dt){
        for(Ptr& child: children){
            child->update(dt);
        }
    }

    sf::Transform getWorldTransform() const {
        sf::Transform returnValue = sf::Transform::Identity;

        for(const GameObject* node = this; node != nullptr; node = node->parent){
            returnValue = node->getTransform() * returnValue;
        }

        return returnValue;
    }

    sf::Vector2f getWorldPosition() const {
        sf::Vector2f returnValue = getWorldTransform() * sf::Vector2f();
        return returnValue;
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        drawCurrent(target, states);
        for (auto itr = children.begin(); itr != children.end(); ++itr){
            (*itr)->draw(target, states);
        }
    }

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

    }

};