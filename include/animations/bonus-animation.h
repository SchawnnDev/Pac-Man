#pragma once

#include "../sprite-animation.h"

class BonusAnimation : public SpriteAnimation {
    int m_ticks;
    bool m_display;
public:
    BonusAnimation();
    ~BonusAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
