#pragma once

#include "../../sprite-animation.h"

class PacmanDownAnimation : public SpriteAnimation {
    int m_ticks;
public:
    PacmanDownAnimation();
    ~PacmanDownAnimation();

    std::optional<Sprite> display() override;
    void start() override;
};
