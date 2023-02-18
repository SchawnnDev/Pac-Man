#include "../../include/entities/pacman.h"
#include "../../include/sprite-handler.h"

Pacman::Pacman(const std::shared_ptr<Board>& p_board) : Entity(0, 0, 1, Direction::LEFT, p_board) {
    m_pacmanDownAnimation = SpriteHandler::getSpriteAnimation("pacman-down");
    m_pacmanUpAnimation = SpriteHandler::getSpriteAnimation("pacman-up");
    m_pacmanLeftAnimation = SpriteHandler::getSpriteAnimation("pacman-left");
    m_pacmanRightAnimation = SpriteHandler::getSpriteAnimation("pacman-right");
    m_pacmanDyingAnimation = SpriteHandler::getSpriteAnimation("pacman-dying");
    currentAnimation() = m_pacmanLeftAnimation;
}

void Pacman::tick() {

    switch (direction()) {
        case Direction::UP:
            currentAnimation() = m_pacmanUpAnimation;
            break;
        case Direction::DOWN:
            currentAnimation() = m_pacmanDownAnimation;
            break;
        case Direction::LEFT:
            currentAnimation() = m_pacmanLeftAnimation;
            break;
        case Direction::RIGHT:
            currentAnimation() = m_pacmanRightAnimation;
            break;
    }

    // Move pacman to next
    if (board()->canEntityMoveTo(this, direction())) {
        position() = position().getPositionAt(direction());
        currentAnimation()->freeze() = false;
    } else {
        currentAnimation()->freeze() = true;
    }

}

Pacman::~Pacman() = default;
