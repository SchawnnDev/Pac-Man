#pragma once

#include "screen.h"
#include "game/level.h"
#include "utils/shared_value.h"
#include "game/game-state.h"
#include "game/player.h"

namespace pacman {

    class GameScreen : public Screen {
        shared_value<GameState> m_gameState;
        shared_value<LevelState> m_levelState;
        PlayerPtr& m_currentPlayer;

        TextElement m_player;
        TextElement m_ready;
        TextElement m_gameOver;

    public:
        GameScreen(TextResources p_textResources, shared_value<LevelState> const& p_levelState, shared_value<GameState> const& p_gameState, PlayerPtr& p_currentPlayer);

        void tick() noexcept override;
        void reset() noexcept override;
        void disable() noexcept;

        void updateState(bool p_playerDisplayGameOver);
        void updateCurrentPlayer();
    };

}