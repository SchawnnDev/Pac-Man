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
public:
    explicit Ghost(const Board &p_board, GhostMode ghostMode)
            : Entity({0, 0}, 4, Direction::LEFT, p_board), m_ghostMode(ghostMode),
              m_target{}
    {}

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

    void startFrightenedMode();

    void startEatenMode();

    void handleScatterMode();
    virtual void handleHomeMode() noexcept = 0;
    virtual void handleChaseTarget(const Entity& p_pacman) noexcept = 0;
};