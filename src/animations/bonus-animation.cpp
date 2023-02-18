#include "../../include/animations/bonus-animation.h"

BonusAnimation::~BonusAnimation() {

}

BonusAnimation::BonusAnimation() : SpriteAnimation({"bonus"}) {
    m_ticks = 0;
    m_display = true;
}

std::shared_ptr<Sprite> BonusAnimation::display() {

    if (m_ticks > 10) {
        m_ticks = 0;
        m_display = !m_display;
    }

    m_ticks++;

    return m_display ? sprites()[0] : nullptr;
}

void BonusAnimation::start() {
    SpriteAnimation::start();
}

