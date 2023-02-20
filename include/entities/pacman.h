#pragma once

#include <utility>

#include "entity.h"
#include "sprite-animation-structs.h"

enum class PacmanState
{
    LIVING,
    DYING
};

class Pacman : public Entity
{
    PacmanAnimations m_animations;
public:

    Pacman(const Board &p_board, PacmanAnimations p_pacmanAnimations) : Entity(
            0, 0, 1, Direction::LEFT, p_board),
            m_animations(std::move(p_pacmanAnimations)) {}

    ~Pacman() override;

    void tick() override;

    [[nodiscard]] inline EntityType entityType() const override
    { return EntityType::Banana; };
};
