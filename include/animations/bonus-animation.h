#pragma once

#include "sprite-animation.h"

class BonusAnimation : public SpriteAnimation {
    int m_ticks;
    bool m_display;
public:
    BonusAnimation();
    ~BonusAnimation();

    void start() override;

    std::optional<Sprite> display() override;
};
