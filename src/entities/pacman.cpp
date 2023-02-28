#include "entities/pacman.h"

void Pacman::tick() noexcept {

    if(!Board::isCase(position())) {
        position().moveAt(direction(), speed());
        std::cout << "pacman move to " << position() << std::endl;
    } else {
        if(canMoveTo(direction()))
        {
            position().moveAt(direction(), speed());
            std::cout << "pacman move to " << position() << std::endl;
        } else {
            currentAnimation()->freeze() = true;
        }
    }

}

void Pacman::changeAnimation() noexcept {
    currentAnimation()->freeze() = false;

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

Pacman::~Pacman() = default;
