#pragma once

#include "ghost.h"
#include "sprite-animation-structs.h"

class Blinky : public Ghost
{
    BlinkyAnimations m_animations;
public:
    Blinky(const Board &p_board, BlinkyAnimations p_animations)
            : Ghost(p_board, GhostMode::Scatter),
              m_animations(std::move(p_animations))
    {}

    ~Blinky() override;

    void tick() override;
};