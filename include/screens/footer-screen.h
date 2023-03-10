#pragma once

#include "screen.h"
#include "utils/shared_value.h"
#include "game.h"

namespace pacman {

    class FooterScreen : public Screen {
        const int m_charSize = 20;
        const int m_spacing = 3;
        TextElement m_creditText;

        shared_value<int> m_credit;
    public:

        FooterScreen(TextResources p_textResources, shared_value<int> p_credit);

        void tick() noexcept override;

        void reset() noexcept override;

        void updateCredit() noexcept;

        void updateState() noexcept;

    };

}