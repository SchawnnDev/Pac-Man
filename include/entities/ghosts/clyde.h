#pragma once

#include "ghost.h"
#include "sprite-animation-structs.h"

class Clyde : public Ghost
{
public:
    Clyde(const Board &p_board, const GhostAnimations& p_animations)
            : Ghost(p_board, GhostMode::House, p_animations)
    {
        position() = getPosition(10, 10);
    }

    ~Clyde() override = default;

    void tick() noexcept override;

    void startScatterMode() noexcept override;

    void startChaseMode() noexcept override;

    void handleHomeMode() noexcept override;

    void handleChaseTarget(const Entity& p_pacman) noexcept override;
};