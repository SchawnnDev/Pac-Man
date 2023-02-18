#pragma once

#include "../../sprite-animation.h"

class PacmanUpAnimation : public SpriteAnimation {
    int m_ticks;
public:
    PacmanUpAnimation();
    ~PacmanUpAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
