#include "../../include/entities/banana.h"

Banana::Banana() : Entity(0, 0) {
    auto bananaDyingAnimation = std::make_shared<BananaDyingAnimation>();
    auto bananaUpAnimation = std::make_shared<BananaDyingAnimation>();
    auto bananaDownAnimation = std::make_shared<BananaDyingAnimation>();
    auto bananaLeftAnimation = std::make_shared<BananaDyingAnimation>();
    auto bananaRightAnimation = std::make_shared<BananaDyingAnimation>();
    m_animations = {
            bananaUpAnimation,
            bananaDownAnimation,
            bananaLeftAnimation,
            bananaRightAnimation,
            bananaDyingAnimation
    };
    currentAnimation() = m_animations[0];
}

void Banana::Tick() {

}

Banana::~Banana() = default;
