#include "entities/ghosts/blinky.h"

void Blinky::tick() noexcept {
    auto actualCase = board().getBoardCaseAtPixels(position());

    if(!actualCase) return; // could and should not happen

    // On position
    if (!Board::isCase(position())) {
        position().moveAt(direction(), speed());
    } else { // actualCase cannot be null

        // TODO: review this (should be 40%)
        if (actualCase->isTunnel()) {
            speed() = 2;
        } else if (speed() == 2) {
            speed() = 4;
        }

        if (direction() == Direction::RIGHT && actualCase->type() == BoardCaseType::DoorRight) {
            auto boardCase = board().grid()[board().leftDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
        } else if (direction() == Direction::LEFT && actualCase->type() == BoardCaseType::DoorLeft) {
            auto boardCase = board().grid()[board().rightDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
        } else {
            auto pairs = std::vector<DirectionBoardCasePair>{};

            // Ghost is on a tile, and he must choose a direction
            auto frontCase = board().getBoardCaseAtPixels(position(), direction());
            auto leftDirection = getDirectionByAngle(direction(), 90);
            auto leftCase = board().getBoardCaseAtPixels(position(), leftDirection);
            auto rightDirection = getDirectionByAngle(direction(), -90);
            auto rightCase = board().getBoardCaseAtPixels(position(), rightDirection);


            if (frontCase && !(direction() == Direction::UP && actualCase->type() == BoardCaseType::GhostUpForbidden)) {
                pairs.emplace_back(direction(), frontCase);
            }

            if (leftCase && !(leftDirection == Direction::UP && actualCase->type() == BoardCaseType::GhostUpForbidden)) {
                pairs.emplace_back(leftDirection, leftCase);
            }

            if (rightCase && !(rightDirection == Direction::UP && actualCase->type() == BoardCaseType::GhostUpForbidden)) {
                pairs.emplace_back(rightDirection, rightCase);
            }

            auto foundCase = getClosestBoardCase(target(), pairs);

            // foundCase should not be null
            if (foundCase.second) {
                move(foundCase.first);
                position().moveAt(direction(), speed());
            }

        }

    }

}

void Blinky::changeAnimation() noexcept {
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

void Blinky::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {BOARD_SIZE_X - 3, -3};
}

void Blinky::startChaseMode() noexcept {
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
}

void Blinky::handleChaseTarget(const Entity &p_pacman) noexcept {
    if (ghostMode() != GhostMode::Chase) return;

    auto position = Board::findCase(p_pacman.position());
    // move 4 cases in the front of blinky
    position.moveAt(p_pacman.direction(), 4);

    // move 4 cases to the left if pacman is going up (specific)
    if (p_pacman.direction() == Direction::UP) {
        position.moveAt(Direction::LEFT, 4);
    }

    target() = position;
}

void Blinky::handleHomeMode() noexcept {}

Blinky::~Blinky() = default;
