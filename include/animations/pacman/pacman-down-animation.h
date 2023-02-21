#pragma once

#include "sprite-animation.h"

class PacmanDownAnimation : public SpriteAnimation {
    int m_ticks;
public:
    explicit PacmanDownAnimation(std::vector<Sprite> &&sprites);
    ~PacmanDownAnimation() = default;

    std::optional<Sprite> display() override;
    void start() override;
};
