#pragma once

#include "sprite-animation.h"

class PacmanRightAnimation : public SpriteAnimation {
    int m_ticks;
public:
    explicit PacmanRightAnimation(std::vector<Sprite> &&sprites);
    ~PacmanRightAnimation() = default;

    std::optional<Sprite> display() override;
    void start() override;
};
