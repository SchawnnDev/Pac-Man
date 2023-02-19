#pragma once

#include "../../sprite-animation.h"

class PacmanLeftAnimation : public SpriteAnimation {
    int m_ticks;
public:
    PacmanLeftAnimation();
    ~PacmanLeftAnimation();

    std::optional<Sprite> display() override;
    void start() override;
};
