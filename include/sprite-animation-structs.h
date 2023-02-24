#pragma once

#include "sprite-animation.h"

struct PacmanAnimations final
{
    SpriteAnimation upAnimation;
    SpriteAnimation downAnimation;
    SpriteAnimation leftAnimation;
    SpriteAnimation rightAnimation;
    SpriteAnimation dyingAnimation;
};

struct BlinkyAnimations final
{
    SpriteAnimation upAnimation;
    SpriteAnimation downAnimation;
    SpriteAnimation leftAnimation;
    SpriteAnimation rightAnimation;
};
