#pragma once

#include <utility>

#include "entity.h"
#include "sprites/sprite-resources-structs.h"

namespace pacman {

    enum class PacmanState {
        LIVING,
        DYING
    };

    class Pacman : public Entity {
        PacmanState m_state;
        PacmanAnimations m_animations;
    public:

        Pacman(const Board &p_board, PacmanAnimations p_pacmanAnimations);

        ~Pacman() override;

        /**
         * @brief Tick logic, handles intern entities logic
         * @override
         */
        void tick() override;

        /**
         * @brief Changes animations according to direction, state
         * @override
         */
        void changeAnimation() override;

        /**
         * @brief Reset all variables to default
         * @override
         */
        void reset() override;

        /**
         * @return Type of entity
         * @override
         */
        [[nodiscard]] inline EntityType entityType() const override { return EntityType::Pacman; };

        /**
         * @return Current Pacman state
         */
        [[nodiscard]] PacmanState state() const { return m_state; }

        /**
         * @return Reference to current pacman state
         */
        PacmanState &state() { return m_state; }

        /**
         * @brief Start die animation
         */
        void die();
    };

}