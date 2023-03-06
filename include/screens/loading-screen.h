#pragma once

#include "screen.h"

namespace pacman {

    class LoadingScreen : public Screen {

        void tick() noexcept override;

    };

}