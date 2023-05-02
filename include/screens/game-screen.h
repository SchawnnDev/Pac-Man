#pragma once

#include "screen.h"
#include "game/level.h"
#include "utils/shared_value.h"
#include "game/game-state.h"
#include "game/player.h"

namespace pacman {

    /**
     * @class GameScreen
     *
     * @brief A screen that displays the game state.
     *
     * The GameScreen class displays the game state, including the current player,
     * the game over message, and the ready message.
     */
    class GameScreen : public Screen {
        shared_value<GameState> m_gameState;
        shared_value<LevelState> m_levelState;
        PlayerPtr& m_currentPlayer;

        TextElement m_player;
        TextElement m_ready;
        TextElement m_gameOver;

    public:

        /**
         * @brief Constructor for the GameScreen class.
         *
         * @param p_textResources The text resources to use.
         * @param p_levelState A shared value that holds the current level state.
         * @param p_gameState A shared value that holds the current game state.
         * @param p_currentPlayer A pointer to the current player object.
         */
        GameScreen(TextResources p_textResources, shared_value<LevelState> const& p_levelState, shared_value<GameState> const& p_gameState, PlayerPtr& p_currentPlayer);

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
          * @brief Disables the screen.
          */
        void disable();

        /**
         * @brief Updates the game state on the screen.
         *
         * @param p_playerDisplayGameOver True if the player has lost the game and the game over message should be displayed.
         */
        void updateState(bool p_playerDisplayGameOver);

        /**
         * @brief Updates the current player.
         */
        void updateCurrentPlayer();
    };

}