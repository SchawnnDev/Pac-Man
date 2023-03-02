#pragma once

#include "utils/position.h"
#include "entities/entity.h"

enum class GhostMode
{
    House, // At start of pacman, ghosts are in house
    Scatter,
    Chase,
    Frightened,
    Eaten
};

class Ghost : public Entity
{
    GhostMode m_ghostMode;
    Position m_target;
    GhostAnimations m_ghostAnimations;
public:
    Ghost(const Board &p_board, GhostMode p_ghostMode, GhostAnimations p_ghostAnimations)
            : Entity({0, 0}, 4, Direction::LEFT, p_board)
            , m_ghostMode(p_ghostMode)
            , m_target{}
            , m_ghostAnimations{std::move(p_ghostAnimations)}
    {
        currentAnimation() = m_ghostAnimations.leftAnimation;
    }

    ~Ghost() override;

    [[nodiscard]] inline EntityType entityType() const override
    {
        return EntityType::Ghost;
    }

    [[nodiscard]] GhostMode const& ghostMode() const { return m_ghostMode; }
    GhostMode &ghostMode() { return m_ghostMode; }

    [[nodiscard]] Position const& target() const { return m_target; }
    Position &target() { return m_target; }

    virtual void startScatterMode() noexcept = 0;
    virtual void startChaseMode() noexcept = 0;
    virtual void handleHomeMode() noexcept = 0;
    virtual void handleChaseTarget(const Entity& p_pacman) noexcept = 0;

    void startFrightenedMode() noexcept;
    void startEatenMode() noexcept;
    void handleScatterMode() noexcept;
    void handlePathFinding() noexcept;
    void handleMovement() noexcept;
    void changeAnimation() noexcept override;

};