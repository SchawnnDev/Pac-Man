#pragma once

#include "screen.h"
#include "level.h"
#include "utils/shared_value.h"

namespace pacman {

    class GameScreen : public Screen {

        shared_value<LevelState> m_levelState;

        TextElement m_player;
        TextElement m_ready;

    public:
        GameScreen(TextResources p_textResources, shared_value<LevelState> const& p_levelState);

        void tick() noexcept override;
        void reset() noexcept override;
        void disable() noexcept;

        void updateState();
    };

}