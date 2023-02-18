#include "../include/sprite-animation.h"
#include "../include/sprite-handler.h"

SpriteAnimation::SpriteAnimation(const std::vector<std::shared_ptr<Sprite>> &sprites) {
    m_sprites = sprites;
    m_activated = false;
    m_freeze = false;
}

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
