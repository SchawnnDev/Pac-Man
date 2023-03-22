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
        SpriteAnimation frightenedEndAnimation;
        SpriteAnimation eyesUpAnimation;
        SpriteAnimation eyesDownAnimation;
        SpriteAnimation eyesLeftAnimation;
        SpriteAnimation eyesRightAnimation;
    };

    struct BoardResources final {
        SpriteAnimation bonusAnimation;
        Sprite pointSprite;
        SpriteAnimation boardAnimation;
        SpriteAnimation boardLevelEndAnimation;
    };

    struct TextResources final {
        std::unordered_map<char, Sprite> const& alphabetSprites;
    };

    struct LoadingScreenResources final {
        Sprite nothingSprite;
        Sprite blinkyRight;
        Sprite pinkyRight;
        Sprite inkyRight;
        Sprite clydeRight;
        Sprite pointSprite;
        Sprite ptsSprite;
        Sprite score10Sprite;
        Sprite score50Sprite;
        SpriteAnimation bonusAnimation;
    };

    struct FooterScreenResources final {
        std::array<Sprite, 8> const& fruitsSprites;
        Sprite lifeSprite;
    };

}