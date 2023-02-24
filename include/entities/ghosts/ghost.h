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
            : Entity(0, 0, 1, Direction::LEFT, p_board), m_ghostMode(ghostMode),
              m_target{}
    {}

    ~Ghost() override;

    [[nodiscard]] inline EntityType entityType() const override
    {
        return EntityType::Ghost;
    }

    [[nodiscard]] const GhostMode &ghostMode() const
    { return m_ghostMode; };

    GhostMode &ghostMode()
    { return m_ghostMode; };

    void startScatterMode();

    void startChaseMode();

    void startFrightenedMode();

    void startEatenMode();

};