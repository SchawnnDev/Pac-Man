#pragma once

#include "screen.h"
#include "utils/shared_value.h"
#include "game/player.h"

namespace pacman {

    /**
     * @class HeaderScreen
     *
     * @brief A screen that displays the header.
     *
     * The HeaderScreen class displays the header, including the high score,
     * the current player, and the current player's score.
     */
    class HeaderScreen : public Screen
    {
        const int m_charSize = 20;
        const int m_spacing = 3;

        shared_value<int> m_highScore;
        shared_value<int> m_playerCount;
        PlayerPtr& m_currentPlayer;

        TextElement m_oneUp;
        TextElement m_highScoreTitle;
        TextElement m_twoUp;
        TextElement m_score1up;
        TextElement m_score2up;
        TextElement m_highScoreText;

    public:

        /**
         * @brief Constructor for the HeaderScreen class.
         *
         * @param p_textResources The text resources to use.
         * @param p_highScore A shared value that holds the high score.
         * @param p_playerCount A shared value that holds the number of players.
         * @param p_currentPlayer A pointer to the current player object.
         */
        HeaderScreen(TextResources p_textResources, const shared_value<int>& p_highScore,
                     shared_value<int> const& p_playerCount, PlayerPtr &p_currentPlayer);

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
         * @brief Updates the high score on the screen.
         */
        void updateHighScore();

        /**
         * @brief Updates the score for the given player on the screen.
         *
         * @param p_playerId The ID of the player whose score to update.
         */
        void updateScore(int p_playerId);

        /**
         * @brief Updates the players shown on the screen (1UP or 1UP + 2UP)
         */
        void updatePlayerCount();
    };

}