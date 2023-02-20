#include "../../include/entities/pacman.h"
#include "../../include/sprite-handler.h"

Pacman::Pacman(const Board& p_board) : Entity(0, 0, 1, Direction::LEFT, p_board) {

    currentAnimation() = m_pacmanLeftAnimation;
}

void Pacman::tick() {

    switch (direction()) {
        case Direction::UP:
            currentAnimation() = m_animations.pacmanUpAnimation;
            break;
        case Direction::DOWN:
            currentAnimation() = m_animations.pacmanDownAnimation;
            break;
        case Direction::LEFT:
            currentAnimation() = m_animations.pacmanLeftAnimation;
            break;
        case Direction::RIGHT:
            currentAnimation() = m_animations.pacmanRightAnimation;
            break;
    }

    // Move pacman to next
    if (canMoveTo(direction())) {
        position() = position().getPositionAt(direction());
        currentAnimation()->freeze() = false;
    } else {
        currentAnimation()->freeze() = true;
    }

}

Pacman::~Pacman() = default;
