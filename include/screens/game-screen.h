#pragma once

#include "screen.h"

namespace pacman {

    class GameScreen : public Screen {

        TextElement m_player;
        TextElement m_ready;

    public:
        explicit GameScreen(TextResources p_textResources);

        void tick() noexcept override;
        void reset() noexcept override;
        void disable() noexcept;
    };

}