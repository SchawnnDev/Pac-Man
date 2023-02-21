#pragma once

#include "sprite-animation.h"

class PacmanLeftAnimation : public SpriteAnimation {
    int m_ticks;
public:
    explicit PacmanLeftAnimation(std::vector<Sprite> &&sprites);
    ~PacmanLeftAnimation() = default;

    std::optional<Sprite> display() override;
    void start() override;
};
