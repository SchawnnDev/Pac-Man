#pragma once

#include "utils/position.h"
#include "entities/entity.h"
#include "entities/pacman.h"

namespace pacman {

    enum class GhostMode {
        Home, // At start of pacman, ghosts are at home
        Scatter,
        Chase,
        Eaten
    };

    class Ghost : public Entity {
        GhostMode m_ghostMode;
        Position m_target;
        GhostAnimations const &m_ghostAnimations;
        Pacman const &m_pacman;
        bool m_frightened;
        int m_dotsCounter;
        int m_ticks;
    protected:
        [[nodiscard]] Pacman const &pacman() const { return m_pacman; }

        virtual void handleChaseTarget() noexcept = 0;

        void handleScatterMode() noexcept;

        void handleHomeMode() noexcept;

        void handleEatenMode() noexcept;

        void handleMovement() noexcept;

        void changeAnimation() noexcept override;

        std::optional<BoardCase> handlePathFinding() noexcept;

        void turnAround() noexcept;

        auto getPossibleDirections(bool withOpposite = false, bool noUp = true, bool checkPracticable = false) noexcept;

    public:
        Ghost(Board const &p_board, Pacman const &p_pacman, GhostMode p_ghostMode,
              GhostAnimations const &p_ghostAnimations)
                : Entity({0, 0}, 4, Direction::LEFT, p_board), m_ghostMode(p_ghostMode), m_target{},
                  m_ghostAnimations{p_ghostAnimations}, m_pacman{p_pacman}, m_dotsCounter{0}, m_ticks{0},
                  m_frightened{false} {
            currentAnimation() = m_ghostAnimations.leftAnimation;
        }

        ~Ghost() override;

        [[nodiscard]] GhostMode ghostMode() const { return m_ghostMode; }
        GhostMode &ghostMode() { return m_ghostMode; }

        [[nodiscard]] Position const &target() const { return m_target; }
        Position &target() { return m_target; }

        [[nodiscard]] int dotsCounter() const { return m_dotsCounter; }
        int& dotsCounter() { return m_dotsCounter; }

        [[nodiscard]] int ticks() const { return m_dotsCounter; }
        int& ticks() { return m_dotsCounter; }

        [[nodiscard]] bool frightened() const { return m_frightened; }
        bool& frightened() { return m_frightened; }

        virtual void startScatterMode() noexcept = 0;

        void startChaseMode() noexcept;

        void startHomeMode() noexcept;

        void startFrightenedMode() noexcept;

        void startEatenMode() noexcept;

    };

    static constexpr int getPriority(const Ghost& ghost) noexcept {
        switch (ghost.entityType()) {
            case EntityType::Pinky:
                return 2;
            case EntityType::Inky:
                return 1;
            case EntityType::Clyde:
                return 0;
            default:
                return -1;
        }
    }

}