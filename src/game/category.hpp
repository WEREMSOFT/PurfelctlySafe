#pragma once

// Categories are used to map the commands with objects. You can send a command into the scene graph
// and manipulate a type of objects, with lambdas, without adding complexity to your entity.
// As an example, an enemy ship can have a acceleration behavior shared by an asteroid.
namespace Category {
    enum Type{
        NONE = 0,
        SCENE = 1,
        BACKGROUND = 1 << 2,
        TABLE = 1 << 3,
        CAT_1 = 1 << 4,
        CAT_2 = 1 << 5
    };
};


