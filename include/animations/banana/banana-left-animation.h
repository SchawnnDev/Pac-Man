#pragma once

#include "../../sprite-animation.h"

class BananaLeftAnimation : public SpriteAnimation {
    int m_ticks;
public:
    BananaLeftAnimation();
    ~BananaLeftAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
