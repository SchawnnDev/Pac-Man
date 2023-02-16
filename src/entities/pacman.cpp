#include "../../include/entities/pacman.h"

Pacman::Pacman() : Entity(0, 0, 1, Direction::UP) {
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

void Pacman::tick() {

}

Pacman::~Pacman() = default;
