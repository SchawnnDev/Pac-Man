#pragma once

#include "screen.h"
#include "utils/shared_value.h"
#include "screens/elements/image.h"
#include "game/game-state.h"
#include "game/player.h"

namespace pacman {

    /**
     * @class FooterScreen
     *
     * @brief A screen that displays information about the player's game state.
     *
     * The FooterScreen class displays information about the player's game state, including
     * the number of lives remaining, the number of credits available, and the current
     * level.
     */
    class FooterScreen : public Screen {
        const int m_charSize = 20;
        const int m_spacing = 3;
        TextElement m_creditText;

        std::array<ImageElement, 3> m_livesImages;
        std::array<ImageElement, FRUITS_DISPLAYED> m_fruits;

        shared_value<int> m_credit;
        shared_value<GameState> m_gameState;
        PlayerPtr& m_currentPlayer;
        FooterScreenResources const& m_footerResources;
    public:

        /**
         * @brief Constructor for the FooterScreen class.
         *
         * @param p_textResources The text resources to use.
         * @param p_credit A shared value that holds the number of credits available.
         * @param p_gameState A shared value that holds the current game state.
         * @param p_currentPlayer A pointer to the current player object.
         * @param p_footerResources The resources used by the screen.
         */
        FooterScreen(TextResources p_textResources, shared_value<int> p_credit,
                     shared_value <GameState> p_gameState,
                     PlayerPtr &p_currentPlayer,
                     const FooterScreenResources& p_footerResources);

        /**
         * @brief Performs a tick of the screen.
         * @override
         */
        void tick() override;

        /**
         * @brief Resets the screen to its initial state.
         * @override
         */
        void reset() override;

        /**
         * @brief Updates the credit count on the screen.
         */
        void updateCredit();

        /**
         * @brief Updates the game state on the screen.
         */
        void updateState();

        /**
         * @brief Updates the remaining lives on the screen.
         */
        void updateLives();

        /**
         * @brief Updates the current level on the screen.
         */
        void updateLevels();

    };

}