#pragma once

#include "../../sprite-animation.h"

class PacmanDyingAnimation : public SpriteAnimation {
    int m_ticks;
public:
    PacmanDyingAnimation();
    ~PacmanDyingAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
