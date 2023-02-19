#include "../include/sprite-animation.h"
#include "../include/sprite-handler.h"

SpriteAnimation::SpriteAnimation(std::initializer_list<std::string> args) {
    for (const auto &sp: args) {
        m_sprites.push_back(SpriteHandler::getSprite(sp));
    }
    m_activated = false;
    m_freeze = false;
}

SpriteAnimation::~SpriteAnimation() {

}

void SpriteAnimation::start() {
    m_activated = true;
}

void SpriteAnimation::stop() {
    m_activated = false;
}
