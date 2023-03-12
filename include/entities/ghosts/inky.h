#pragma once

#include "ghost.h"
#include "sprite-resources-structs.h"

namespace pacman {

    class Inky : public Ghost {

        Ghost const &m_blinky;

    public:
        Inky(Board const &p_board, Pacman const &p_pacman, Ghost const &p_blinky, GhostAnimations const &p_animations)
                : Ghost(p_board, p_pacman, GhostMode::Home, p_animations), m_blinky{p_blinky} {
            position() = getPosition(10, 10);
        }

        ~Inky() override = default;

        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Inky; };

        void tick() noexcept override;

        void reset() noexcept override;

        void startScatterMode() noexcept override;

        void startChaseMode() noexcept override;

        void handleChaseTarget() noexcept override;
    };

}