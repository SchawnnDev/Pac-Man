#include "../../../include/animations/banana/banana-dying-animation.h"

BananaDyingAnimation::BananaDyingAnimation()
        : SpriteAnimation({"banana_dying_1", "banana_dying_2", "banana_dying_3",
                           "banana_dying_4", "banana_dying_5", "banana_dying_6",
                           "banana_dying_7", "banana_dying_8", "banana_dying_9", "banana_dying_10"}) {
    m_ticks = -1;
}

BananaDyingAnimation::~BananaDyingAnimation() {

}

std::shared_ptr<Sprite> BananaDyingAnimation::display() {
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

void BananaDyingAnimation::start() {
    if(activated()) return;
    SpriteAnimation::start();
    m_ticks = -1;
}

