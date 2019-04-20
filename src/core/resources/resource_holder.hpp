#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


template <typename Resource, typename Identifier>
struct ResourceHolder {
private:
    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
public:
    void load(Identifier id, const std::string& filename){
        std::unique_ptr<Resource> resource(new Resource());
        assert(resource->loadFromFile(filename) && "ERROR!! SOMETHING WHEN WRONG LOADING RESOURCE ");
        auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
        assert(inserted.second);
    }

    Resource& get(Identifier id) const {
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    }
    ResourceHolder(){
        std::cout << "construyendo the resorce holder" << std::endl;
    }

    ~ResourceHolder(){
        std::cout << "destroying the resorce holder" << std::endl;
    }
};

