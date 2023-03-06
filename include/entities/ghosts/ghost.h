#pragma once

#include "utils/position.h"
#include "entities/entity.h"
#include "entities/pacman.h"

namespace pacman {

    enum class GhostMode {
        House, // At start of pacman, ghosts are in house
        Scatter,
        Chase,
        Frightened,
        Eaten
    };

    class Ghost : public Entity {
        GhostMode m_ghostMode;
        Position m_target;
        GhostAnimations const &m_ghostAnimations;
        Pacman const &m_pacman;
    protected:
        [[nodiscard]] Pacman const &pacman() const { return m_pacman; }

    public:
        Ghost(Board const &p_board, Pacman const &p_pacman, GhostMode p_ghostMode,
              GhostAnimations const &p_ghostAnimations)
                : Entity({0, 0}, 4, Direction::LEFT, p_board), m_ghostMode(p_ghostMode), m_target{},
                  m_ghostAnimations{p_ghostAnimations}, m_pacman{p_pacman} {
            currentAnimation() = m_ghostAnimations.leftAnimation;
        }

        ~Ghost() override;

        [[nodiscard]] inline EntityType entityType() const override {
            return EntityType::Ghost;
        }

        [[nodiscard]] GhostMode ghostMode() const { return m_ghostMode; }

        GhostMode &ghostMode() { return m_ghostMode; }

        [[nodiscard]] Position const &target() const { return m_target; }

        Position &target() { return m_target; }

        virtual void startScatterMode() noexcept = 0;

        virtual void startChaseMode() noexcept = 0;

        virtual void handleHomeMode() noexcept = 0;

        virtual void handleChaseTarget() noexcept = 0;

        void startFrightenedMode() noexcept;

        void startEatenMode() noexcept;

        void handleScatterMode() noexcept;

        std::optional<BoardCase> handlePathFinding() noexcept;

        void handleMovement() noexcept;

        void changeAnimation() noexcept override;

    };

}