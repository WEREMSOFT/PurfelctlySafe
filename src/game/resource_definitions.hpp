#pragma once

#include "../core/resources/resource_holder.hpp"

namespace Textures{
    enum ID {
        BACKGROUND,
        TABLE,
        HOUSE,
        LIGHT_O_TABLE,
        TITLE_BACKGROUND_TILE,
        TITLE_MAIN_IMAGE,
        CAT_1_ANIMATION,
        CAT_2_ANIMATION,
        TEXTURE_COUNT
    };
}

namespace Fonts{
    enum ID {
        PRESS_START,
        FONT_COUNT
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
