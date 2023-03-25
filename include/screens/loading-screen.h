#pragma once

#include "screen.h"
#include "screens/elements/image.h"
#include "utils/shared_value.h"

#include <utility>

namespace pacman {

    /**
     * @class LoadingScreen
     * @brief Represents the screen that shows up when user has no credits
     *      and when user has credits and must select player count
     */
    class LoadingScreen : public Screen {
        const int m_ghostX = WINDOW_SIZE_WIDTH / 2 - CALC(9);
        const int m_scoreY = WINDOW_SIZE_HEIGHT / 4 * 3 - 40;

        SpriteAnimation m_bonusAnimation;
        Sprite m_nothingSprite;

        // Texts
        TextElement m_charNick;
        TextElement m_blinky;
        TextElement m_pinky;
        TextElement m_inky;
        TextElement m_clyde;
        TextElement m_midway;

        // Images
        ImageElement m_blinkyImage;
        ImageElement m_pinkyImage;
        ImageElement m_inkyImage;
        ImageElement m_clydeImage;
        ImageElement m_score10Image;
        ImageElement m_score50Image;
        ImageElement m_score10PtsImage;
        ImageElement m_score50PtsImage;
        ImageElement m_pointImage;
        ImageElement m_bonusImage;

        // Second screen (when credit)
        TextElement m_startButton;
        TextElement m_players;
        TextElement m_bonusPacman;
        ImageElement m_bonusPacmanPtsImage;

        shared_value<int> m_credit;
    public:

        /**
         * @brief Constructs a new LoadingScreen object.
         * @param p_resources The resources for the screen.
         * @param p_textResources The text resources for the screen.
         * @param p_credit The shared value for the game credit count.
         */
        LoadingScreen(const LoadingScreenResources &p_resources, TextResources p_textResources,
                      shared_value<int> p_credit);

        void tick() noexcept override;
        void reset() noexcept override;
        void disable() noexcept;

        /**
         * @brief Updates the credit count displayed on the screen.
         * Also switches the screen from "no credit" to "player select"
         */
        void updateCredit() noexcept;

    };

}