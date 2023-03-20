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

        void tick() noexcept override;

        void changeAnimation() noexcept override;

        void reset() noexcept override;

        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Pacman; };

        [[nodiscard]] PacmanState state() const noexcept { return m_state; }

        PacmanState &state() noexcept { return m_state; }

        void die() noexcept;
    };

}