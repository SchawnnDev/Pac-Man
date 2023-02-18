#pragma once

#include "entity.h"

enum class PacmanState {
    LIVING,
    DYING
};

class Pacman : public Entity
{
    std::shared_ptr<SpriteAnimation> m_pacmanUpAnimation;
    std::shared_ptr<SpriteAnimation> m_pacmanDownAnimation;
    std::shared_ptr<SpriteAnimation> m_pacmanLeftAnimation;
    std::shared_ptr<SpriteAnimation> m_pacmanRightAnimation;
    std::shared_ptr<SpriteAnimation> m_pacmanDyingAnimation;
public:
    explicit Pacman(const std::shared_ptr<Board>& p_board);

    ~Pacman() override;

    void tick() override;

    [[nodiscard]] inline EntityType entityType() const override
    { return EntityType::Banana; };
};