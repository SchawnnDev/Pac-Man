#include "sprite-animation.h"
#include "sprite-handler.h"

SpriteAnimation::SpriteAnimation(std::vector<Sprite> &&p_sprites)
    : m_sprites{p_sprites}
    , m_activated{false}
    , m_freeze{false}
{ }

void SpriteAnimation::start() {
    m_activated = true;
}

void SpriteAnimation::stop() {
    m_activated = false;
}