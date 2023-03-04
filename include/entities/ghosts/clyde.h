#pragma once

#include "ghost.h"
#include "sprite-animation-structs.h"

class Clyde : public Ghost
{
public:
    Clyde(Board const& p_board, Pacman const &p_pacman,  GhostAnimations const& p_animations)
            : Ghost(p_board, p_pacman, GhostMode::House, p_animations)
    {
        position() = getPosition(10, 10);
    }

    ~Clyde() override = default;

    void tick() noexcept override;

    void startScatterMode() noexcept override;

    void startChaseMode() noexcept override;

    void handleHomeMode() noexcept override;

    void handleChaseTarget() noexcept override;
};