#pragma once

#include "ghost.h"
#include "sprite-animation-structs.h"

class Pinky : public Ghost
{
public:
    Pinky(const Board &p_board, const GhostAnimations& p_animations)
            : Ghost(p_board, GhostMode::House, p_animations)
    {
        position() = getPosition(10, 10);
    }

    ~Pinky() override = default;

    void tick() noexcept override;

    void startScatterMode() noexcept override;

    void startChaseMode() noexcept override;

    void handleHomeMode() noexcept override;

    void handleChaseTarget(std::span<const Entity> p_targets) noexcept override;
};