#pragma once

#include "screen.h"
#include "utils/shared_value.h"

namespace pacman {

    class HeaderScreen : public Screen
    {
        const int m_charSize = 20;
        const int m_spacing = 3;

        shared_value<int> m_highScore;
        shared_value<int> m_currentPlayer;
        std::array<shared_value<int>, 2> m_scores;

        TextElement m_oneUp;
        TextElement m_highScoreTitle;
        TextElement m_twoUp;
        TextElement m_score;
        TextElement m_highScoreText;

    public:

        explicit HeaderScreen(TextResources p_textResources, shared_value<int> p_highScore,
                              shared_value<int> p_currentPlayer, std::array<shared_value<int>, 2> p_scores);

        void tick() noexcept override;

        void reset() noexcept override;

        void updateHighScore();

    };

}