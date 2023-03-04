#pragma once

#include "ghost.h"
#include "sprite-animation-structs.h"

class Inky : public Ghost
{

    Ghost const& m_blinky;

public:
    Inky(Board const& p_board, Pacman const &p_pacman, Ghost const& p_blinky, GhostAnimations const& p_animations)
            : Ghost(p_board, p_pacman, GhostMode::House, p_animations)
            , m_blinky{p_blinky}
    {
        position() = getPosition(10, 10);
    }

    ~Inky() override = default;

    void tick() noexcept override;

    void startScatterMode() noexcept override;

    void startChaseMode() noexcept override;

    void handleHomeMode() noexcept override;

    void handleChaseTarget() noexcept override;
};