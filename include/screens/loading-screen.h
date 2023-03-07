#pragma once

#include "screen.h"

#include <utility>

namespace pacman {

    class LoadingScreen : public Screen {
        std::shared_ptr<Text> m_oneUp;
        std::shared_ptr<Text> m_twoUp;
        std::shared_ptr<Text> m_highScore;

    public:

        explicit LoadingScreen(TextResources p_textResources);

        void tick() noexcept override;
        void reset() noexcept override;

    };

}