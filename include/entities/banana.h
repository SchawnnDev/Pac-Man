#pragma once

#include "entity.h"
#include "../animations/banana/banana-dying-animation.h"

class Banana : public Entity
{
    std::vector<std::shared_ptr<SpriteAnimation>> m_animations;
public:
    Banana();
    ~Banana() override;

    void tick() override;
};