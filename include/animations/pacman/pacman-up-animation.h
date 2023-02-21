#pragma once

#include "sprite-animation.h"

class PacmanUpAnimation : public SpriteAnimation {
    int m_ticks;
public:
    explicit PacmanUpAnimation(std::vector<Sprite> &&sprites);
    ~PacmanUpAnimation() = default;

    std::optional<Sprite> display() override;
    void start() override;
};
