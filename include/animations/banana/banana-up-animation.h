#pragma once

#include "../../sprite-animation.h"

class BananaUpAnimation : public SpriteAnimation {
    int m_ticks;
public:
    BananaUpAnimation();
    ~BananaUpAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
