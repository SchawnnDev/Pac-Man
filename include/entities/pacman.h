#pragma once

#include <utility>

#include "entity.h"
#include "sprite-resources-structs.h"

namespace pacman {

    enum class PacmanState {
        LIVING,
        DYING
    };

    class Pacman : public Entity {
        PacmanState m_state;
        PacmanAnimations m_animations;
        int m_lives;
    public:

        Pacman(const Board &p_board, PacmanAnimations p_pacmanAnimations) : Entity(getPosition(10, 20),
                1, Direction::LEFT, p_board),
                m_state{PacmanState::LIVING},
                m_animations(std::move(p_pacmanAnimations)),
                m_lives{2} {
            currentAnimation() = m_animations.leftAnimation;
            speed() = 4;
        }

        ~Pacman() override;

        void tick() noexcept override;

        void changeAnimation() noexcept override;

        [[nodiscard]] inline EntityType entityType() const noexcept override { return EntityType::Pacman; };
    };

}