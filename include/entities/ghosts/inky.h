#pragma once

#include "ghost.h"
#include "sprites/sprite-resources-structs.h"

namespace pacman {

    class Inky : public Ghost {

        Ghost const &m_blinky;

    public:
        Inky(Board const &p_board, Pacman const &p_pacman, Ghost const &p_blinky, GhostAnimations const &p_animations)
                : Ghost(p_board, p_pacman, GhostMode::Home, p_animations), m_blinky{p_blinky} {
            position() = getPosition(10, 10);
        }

        ~Inky() override = default;

        /**
         * @return Type of entity
         * @override
         */
        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Inky; };

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