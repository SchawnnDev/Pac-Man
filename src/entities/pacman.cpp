#include "entities/pacman.h"

void Pacman::tick() noexcept {

    if(m_state == PacmanState::DYING) {
        return;
    }

    if (!Board::isCase(position())) {
        position().moveAt(direction(), speed());
        std::cout << "pacman move to " << position() << std::endl;
    } else {
        if (canMoveTo(direction())) {
            position().moveAt(direction(), speed());
            std::cout << "pacman move to " << position() << std::endl;
        } else {
            // Check if user is at doors, then teleport
            if (board().isOnLeftDoor(position())) {
                auto boardCase = board().grid()[board().rightDoorIndex()];
                position() = getPosition(boardCase.x(), boardCase.y());
            } else if (board().isOnRightDoor(position())) {
                auto boardCase = board().grid()[board().leftDoorIndex()];
                position() = getPosition(boardCase.x(), boardCase.y());
            } else {
                currentAnimation()->freeze() = true;
            }

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
