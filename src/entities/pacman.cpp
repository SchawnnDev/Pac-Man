#include "../../include/entities/pacman.h"
#include "../../include/sprite-handler.h"

void Pacman::tick() {

    switch (direction()) {
        case Direction::UP:
            currentAnimation() = m_animations.upAnimation;
            break;
        case Direction::DOWN:
            currentAnimation() = m_animations.downAnimation;
            break;
        case Direction::LEFT:
            currentAnimation() = m_animations.leftAnimation;
            break;
        case Direction::RIGHT:
            currentAnimation() = m_animations.rightAnimation;
            break;
    }

    // Move pacman to next
    if (canMoveTo(direction())) {
        position() = position().getPositionAt(direction());
        //currentAnimation()->freeze() = false;
    } else {
        //currentAnimation()->freeze() = true;
    }

}

Pacman::~Pacman() = default;
