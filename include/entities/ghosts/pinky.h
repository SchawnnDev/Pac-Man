#pragma once

#include "ghost.h"
#include "sprites/sprite-resources-structs.h"

namespace pacman {

    class Pinky : public Ghost {
    public:
        Pinky(Board const &p_board, Pacman const &p_pacman, GhostAnimations const &p_animations)
                : Ghost(p_board, p_pacman, GhostMode::Home, p_animations) {
            position() = getPosition(10, 10);
        } // pinky millieu orange a droite

        ~Pinky() override = default;

        /**
         * @return Type of entity
         * @override
         */
        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Pinky; };

        /**
         * @brief Reset all variables to default
         * @override
         */
        void reset() noexcept override;

        /**
         * @brief Starts the scatter mode, changing target to a corner
         * @override
         */
        void startScatterMode() noexcept override;

        /**
         * @brief Handles chase target and logic
         * @override
         */
        void handleChaseTarget() noexcept override;

    };

}