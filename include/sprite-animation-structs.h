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

struct GhostAnimations final
{
    SpriteAnimation upAnimation;
    SpriteAnimation downAnimation;
    SpriteAnimation leftAnimation;
    SpriteAnimation rightAnimation;
};

struct BoardResources final {
    SpriteAnimation bonusAnimation;
    Sprite pointSprite;
    Sprite emptyBoardSprite;
};
