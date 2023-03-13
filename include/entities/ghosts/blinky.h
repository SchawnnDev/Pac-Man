#pragma once

#include "ghost.h"
#include "sprite-resources-structs.h"
#include "entities/pacman.h"

namespace pacman {

    class Blinky : public Ghost {
    public:
        Blinky(Board const &p_board, Pacman const &p_pacman, GhostAnimations const &p_animations)
                : Ghost(p_board, p_pacman, GhostMode::Home, p_animations) {
            position() = getPosition(10, 10);
        }

        ~Blinky() override = default;

        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Blinky; };

        void tick() noexcept override;

        void reset() noexcept override;

        void startScatterMode() noexcept override;

        void startChaseMode() noexcept override;

        void handleChaseTarget() noexcept override;

    };

}