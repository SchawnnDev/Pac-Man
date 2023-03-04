#include "entities/ghosts/ghost.h"

using namespace pacman;

Ghost::~Ghost() = default;

void Ghost::startEatenMode() noexcept {

}

void Ghost::startFrightenedMode() noexcept{

}

void Ghost::handleScatterMode() noexcept{

}

void Ghost::handlePathFinding() noexcept {
    if(!currentCase()) return;
    auto& actualCase = currentCase();
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
    }
}

void Ghost::handleMovement() noexcept {
    if(!currentCase()) return;
    auto& actualCase = currentCase();
    auto currentSpeed = speed();

    // TODO: review this (should be 40%)
    if (actualCase->isTunnel()) {
        currentSpeed /= 2;
    }

    if (Board::isCase(position())) { // actualCase cannot be null

        if (direction() == Direction::RIGHT && actualCase->type() == BoardCaseType::DoorRight) {
            auto boardCase = board().grid()[board().leftDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
        } else if (direction() == Direction::LEFT && actualCase->type() == BoardCaseType::DoorLeft) {
            auto boardCase = board().grid()[board().rightDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
        } else {
            handlePathFinding();
        }

    }

    position().moveAt(direction(), currentSpeed);

}

void Ghost::changeAnimation() noexcept {
    currentAnimation()->freeze() = false;

    switch (direction()) {
        case Direction::UP:
            currentAnimation() = m_ghostAnimations.upAnimation;
            break;
        case Direction::DOWN:
            currentAnimation() = m_ghostAnimations.downAnimation;
            break;
        case Direction::LEFT:
            currentAnimation() = m_ghostAnimations.leftAnimation;
            break;
        case Direction::RIGHT:
            currentAnimation() = m_ghostAnimations.rightAnimation;
            break;
    }
}
