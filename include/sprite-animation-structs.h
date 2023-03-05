#pragma once

#include "sprite-animation.h"

namespace pacman {

    struct PacmanAnimations final {
        SpriteAnimation upAnimation;
        SpriteAnimation downAnimation;
        SpriteAnimation leftAnimation;
        SpriteAnimation rightAnimation;
        SpriteAnimation dyingAnimation;
    };

    struct GhostAnimations final {
        SpriteAnimation upAnimation;
        SpriteAnimation downAnimation;
        SpriteAnimation leftAnimation;
        SpriteAnimation rightAnimation;
        SpriteAnimation frightenedAnimation;
    };

    struct BoardResources final {
        SpriteAnimation bonusAnimation;
        Sprite pointSprite;
        Sprite emptyBoardSprite;
    };

}