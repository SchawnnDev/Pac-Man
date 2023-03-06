#pragma once

#include "ghost.h"
#include "sprite-resources-structs.h"

namespace pacman {

    class Pinky : public Ghost {
    public:
        Pinky(Board const &p_board, Pacman const &p_pacman, GhostAnimations const &p_animations)
                : Ghost(p_board, p_pacman, GhostMode::Home, p_animations) {
            position() = getPosition(10, 10);
        } // pinky millieu orange a droite

        ~Pinky() override = default;

        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Pinky; };

        void tick() noexcept override;

        void startScatterMode() noexcept override;

        void startChaseMode() noexcept override;

        void startHomeMode() noexcept override;

        void handleHomeMode() noexcept override;

        void handleChaseTarget() noexcept override;

    };

}