#pragma once

#include "screen.h"
#include "utils/shared_value.h"
#include "screens/elements/image.h"
#include "game-state.h"

namespace pacman {

    class FooterScreen : public Screen {
        const int m_charSize = 20;
        const int m_spacing = 3;
        TextElement m_creditText;

        std::array<ImageElement, 3> m_livesImages;
        std::array<ImageElement, FRUITS_DISPLAYED> m_fruits;

        shared_value<int> m_credit;
        shared_value<GameState> m_gameState;
        std::array<shared_value<int>, 2> m_levels;
        std::array<shared_value<int>, 2> m_lives;
        shared_value<int> m_currentPlayer;
        FooterScreenResources const& m_footerResources;
    public:

        FooterScreen(TextResources p_textResources, shared_value<int> p_credit,
                     shared_value <GameState> p_gameState,
                     std::array<shared_value<int>, 2> const &p_levels,
                     std::array<shared_value<int>, 2> const &p_lives,
                     const FooterScreenResources& p_footerResources);

        void tick() noexcept override;

        void reset() noexcept override;

        void updateCredit() noexcept;

        void updateState() noexcept;

        void updateLives() noexcept;

        void updateLevels() noexcept;

    };

}