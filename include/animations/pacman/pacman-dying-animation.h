#pragma once

#include "sprite-animation.h"

class PacmanDyingAnimation : public SpriteAnimation {
    int m_ticks;
public:
    explicit PacmanDyingAnimation(std::vector<Sprite> &&sprites);
    ~PacmanDyingAnimation() = default;

    std::optional<Sprite> display() override;
    void start() override;
};
