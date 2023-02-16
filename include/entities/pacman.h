#pragma once

#include "entity.h"
#include "../animations/banana/banana-dying-animation.h"

class Pacman : public Entity
{
    std::vector<std::shared_ptr<SpriteAnimation>> m_animations;
public:
    Pacman();

    ~Pacman() override;

    void tick() override;

    [[nodiscard]] inline EntityType entityType() const override
    { return EntityType::Banana; };
};