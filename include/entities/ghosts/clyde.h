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

        /**
         * @return Type of entity
         * @override
         */
        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Clyde; };

        /**
         * @brief Tick logic, handles intern entities logic
         * @override
         */
        void tick() noexcept override;

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