#pragma once

#include "../core/resources/resource_holder.hpp"

namespace Textures{
    enum ID {
        BACKGROUND,
        TABLE,
        HOUSE,
        LIGHT_O_TABLE,
        TITLE_BACKGROUND_TILE,
        TEXTURE_COUNT
    };
}

namespace Fonts{
    enum ID {
        ARIAL
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Textures::ID> FontHolder;
