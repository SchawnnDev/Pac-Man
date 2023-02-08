#pragma once

#include "../../sprite-animation.h"

class BananaRightAnimation : public SpriteAnimation {
    int m_ticks;
public:
    BananaRightAnimation();
    ~BananaRightAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
