#pragma once

#include "ghost.h"
#include "sprites/sprite-resources-structs.h"

namespace pacman {

    class Clyde : public Ghost {
    public:
        Clyde(Board const &p_board, Pacman const &p_pacman, GhostAnimations const &p_animations)
                : Ghost(p_board, p_pacman, GhostMode::Home, p_animations) {
            position() = getPosition(10, 10);
        }

        ~Clyde() override = default;

        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Clyde; };

        void tick() noexcept override;

        void reset() noexcept override;

        void startScatterMode() noexcept override;

        void handleChaseTarget() noexcept override;
    };

}