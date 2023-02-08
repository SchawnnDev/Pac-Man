#pragma once

#include "../../sprite-animation.h"

class BananaDownAnimation : public SpriteAnimation {
    int m_ticks;
public:
    BananaDownAnimation();
    ~BananaDownAnimation();

    std::shared_ptr<Sprite> display() override;
    void start() override;
};
