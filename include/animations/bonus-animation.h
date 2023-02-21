#pragma once

#include "sprite-animation.h"

class BonusAnimation : public SpriteAnimation {
    int m_ticks;
    bool m_display;
public:
    explicit BonusAnimation(std::vector<Sprite> &&sprites);
    ~BonusAnimation() = default;

    void start() override;

    std::optional<Sprite> display() override;
};
