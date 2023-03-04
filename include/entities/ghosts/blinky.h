#pragma once

#include "ghost.h"
#include "sprite-animation-structs.h"

class Blinky : public Ghost
{
public:
    Blinky(const Board &p_board, const GhostAnimations& p_animations)
            : Ghost(p_board, GhostMode::House, p_animations)
    {
        position() = getPosition(10, 10);
    }

    ~Blinky() override = default;

    void tick() noexcept override;

    void startScatterMode() noexcept override;

    void startChaseMode() noexcept override;

    void handleHomeMode() noexcept override;

    void handleChaseTarget(std::convertible_to<Entity> auto ...indices) noexcept override;
};