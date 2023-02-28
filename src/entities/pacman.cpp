#include "entities/pacman.h"

void Pacman::tick() {

    if(lastDirection() != direction())
    {
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
