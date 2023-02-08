#include "../../../include/animations/banana/banana-right-animation.h"

BananaRightAnimation::BananaRightAnimation()
        : SpriteAnimation({"banana_dying_1", "banana_dying_2", "banana_dying_3",
                           "banana_dying_4", "banana_dying_5", "banana_dying_6",
                           "banana_dying_7", "banana_dying_8", "banana_dying_9", "banana_dying_10"}) {
    m_ticks = -1;
}

BananaRightAnimation::~BananaRightAnimation() {

}

std::shared_ptr<Sprite> BananaRightAnimation::display() {
    if(!activated()) return nullptr;
    m_ticks++;

    // first tick
    if(m_ticks <= 0)
    {
        return sprites()[0];
    }

    int idx = m_ticks / 6;

    if(idx > 9)
    {
        activated() = false;
        return nullptr;
    }

    return sprites()[idx];
}

void BananaRightAnimation::start() {
    if(activated()) return;
    SpriteAnimation::start();
    m_ticks = -1;
}

