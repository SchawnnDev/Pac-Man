#pragma once

#include <map>
#include <unordered_map>
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

    struct TextResources final {
        std::unordered_map<char, Sprite> const& alphabetSprites;
        Sprite nothingSprite;
    };

}