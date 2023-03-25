#pragma once

#include <map>
#include <unordered_map>
#include "sprite-animation.h"

namespace pacman {

    /**
     * @brief Struct that contains all animations for pacman
     */
    struct PacmanAnimations final {
        SpriteAnimation upAnimation;
        SpriteAnimation downAnimation;
        SpriteAnimation leftAnimation;
        SpriteAnimation rightAnimation;
        SpriteAnimation dyingAnimation;
    };

    /**
     * @brief Struct that contains all animations for a ghost
     */
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

    /**
     * @brief Struct that contains all resources for the board
     */
    struct BoardResources final {
        SpriteAnimation bonusAnimation;
        Sprite pointSprite;
        SpriteAnimation boardAnimation;
        SpriteAnimation boardLevelEndAnimation;
    };

    /**
     * @brief Struct that contains all sprites to display text
     */
    struct TextResources final {
        std::unordered_map<char, Sprite> const& alphabetSprites;
    };

    /**
     * @brief Struct that contains all resources for the loading screen
     */
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

    /**
     * @brief Struct that contains all resources for the footer screen
     */
    struct FooterScreenResources final {
        std::array<Sprite, 8> const& fruitsSprites;
        Sprite lifeSprite;
    };

    /**
     * @brief Struct that contains all resources for a fruit
     */
    struct FruitResources final {
        std::array<Sprite, 8> const& fruitsSprites;
        std::unordered_map<int, Sprite> const& m_scoresSprites;
    };

}