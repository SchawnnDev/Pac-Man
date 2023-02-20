#include "animations/bonus-animation.h"

BonusAnimation::~BonusAnimation() {

}

BonusAnimation::BonusAnimation() : SpriteAnimation({"bonus"}) {
    m_ticks = 0;
    m_display = true;
}

std::optional<Sprite> BonusAnimation::display() {
    if (!freeze()) {
        if (m_ticks > 10) {
            m_ticks = 0;
            m_display = !m_display;
        }

        m_ticks++;
    }
    return m_display ? std::make_optional<Sprite>(sprites()[0]) : std::nullopt;
}

void BonusAnimation::start() {
    SpriteAnimation::start();
}

