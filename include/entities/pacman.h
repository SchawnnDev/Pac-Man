#pragma once

#include "entity.h"

enum class PacmanState {
    LIVING,
    DYING
};

struct PacmanAnimations final
{
    SpriteAnimation pacmanUpAnimation;
    SpriteAnimation pacmanDownAnimation;
    SpriteAnimation pacmanLeftAnimation;
    SpriteAnimation pacmanRightAnimation;
    SpriteAnimation pacmanDyingAnimation;
};

class Pacman : public Entity
{
    PacmanAnimations m_animations;
public:
    explicit Pacman(Board p_board, PacmanAnimations a);

    ~Pacman() override;

    void tick() override;

    [[nodiscard]] inline EntityType entityType() const override
    { return EntityType::Banana; };
};
