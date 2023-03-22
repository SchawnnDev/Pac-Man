#pragma once

#include "screen.h"
#include "utils/shared_value.h"
#include "game/player.h"

namespace pacman {

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

        HeaderScreen(TextResources p_textResources, const shared_value<int>& p_highScore,
                     shared_value<int> const& p_playerCount, PlayerPtr &p_currentPlayer);

        void tick() noexcept override;

        void reset() noexcept override;

        void updateHighScore() noexcept;

        void updateScore(int p_playerId) noexcept;

        void updatePlayerCount() noexcept;
    };

}