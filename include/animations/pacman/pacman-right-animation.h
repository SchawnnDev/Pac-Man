#pragma once

#include "../../sprite-animation.h"

class PacmanRightAnimation : public SpriteAnimation {
    int m_ticks;
public:
    PacmanRightAnimation();
    ~PacmanRightAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
