#pragma once

#include "screen.h"

namespace pacman {

    class FooterScreen : public Screen {

    public:

        explicit FooterScreen(TextResources p_textResources);

        void tick() noexcept override;

        void reset() noexcept override;
    };

}