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
        PlayerPtr m_currentPlayer;

        TextElement m_oneUp;
        TextElement m_highScoreTitle;
        TextElement m_twoUp;
        TextElement m_score;
        TextElement m_highScoreText;

    public:

        explicit HeaderScreen(TextResources p_textResources, shared_value<int> p_highScore,
                              PlayerPtr p_currentPlayer);

        void tick() noexcept override;

        void reset() noexcept override;

        void updateHighScore() noexcept;

        void updateScore() noexcept;
    };

}