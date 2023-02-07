#pragma once

#include "../sprite-animation.h"

class BananaDyingAnimation : public SpriteAnimation {
    int m_ticks;
public:
    BananaDyingAnimation();
    ~BananaDyingAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
