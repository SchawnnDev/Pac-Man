#include "entities/ghosts/ghost.h"

using namespace pacman;

Ghost::~Ghost() = default;

void Ghost::startEatenMode() noexcept {

}

void Ghost::startFrightenedMode() noexcept{

}

void Ghost::handleScatterMode() noexcept{

}

std::optional<BoardCase> Ghost::handlePathFinding() noexcept {
    if(!currentCase()) return std::nullopt;
    auto& actualCase = currentCase();
    auto pairs = std::vector<DirectionBoardCasePair>{};

    // Ghost is on a tile, and he must choose a direction
    auto frontCase = board().getBoardCaseAtPixels(position(), direction());
    auto leftDirection = getDirectionByAngle(direction(), 90);
    auto leftCase = board().getBoardCaseAtPixels(position(), leftDirection);
    auto rightDirection = getDirectionByAngle(direction(), -90);
    auto rightCase = board().getBoardCaseAtPixels(position(), rightDirection);

    // Specific home mode can also go in backward direction
    if(ghostMode() == GhostMode::Home)
    {
        auto backDirection = getOpposite(direction());
        auto backCase = board().getBoardCaseAtPixels(position(), backDirection);

        if (backCase && !(backDirection == Direction::UP && actualCase->flags() & CASE_FLAG_NO_UP)) {
            pairs.emplace_back(backDirection, backCase);
        }

    }

    if (frontCase && !(direction() == Direction::UP && actualCase->flags() & CASE_FLAG_NO_UP)) {
        pairs.emplace_back(direction(), frontCase);
    }

    if (leftCase && !(leftDirection == Direction::UP && actualCase->flags() & CASE_FLAG_NO_UP)) {
        pairs.emplace_back(leftDirection, leftCase);
    }

    if (rightCase && !(rightDirection == Direction::UP && actualCase->flags() & CASE_FLAG_NO_UP)) {
        pairs.emplace_back(rightDirection, rightCase);
    }

    auto foundCase = pacman::getClosestBoardCase(target(), pairs);

    // foundCase should not be null
    if (foundCase.second) {
        move(foundCase.first);
    }

    return foundCase.second;
}

void Ghost::handleMovement() noexcept {
    if(!currentCase()) return;
    auto const& actualCase = currentCase();
    auto currentSpeed = speed();

    if (Board::isCase(position())) { // actualCase cannot be null

        if (direction() == Direction::RIGHT && actualCase->type() == BoardCaseType::DoorRight) {
            auto& boardCase = board().grid()[board().leftDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
            return;
        }

        if (direction() == Direction::LEFT && actualCase->type() == BoardCaseType::DoorLeft) {
            auto& boardCase = board().grid()[board().rightDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
            return;
        }


        auto const& newCase = handlePathFinding();

        // TODO: convert to fct
        // TODO: review this (should be 40%)
        if (newCase->flags() & CASE_FLAG_TUNNEL_SLOW_DOWN) {
            currentSpeed /= 2;
        }

    } else {

        if (actualCase->flags() & CASE_FLAG_TUNNEL_SLOW_DOWN) {
            currentSpeed /= 2;
        }

    }

/*
    auto next = Board::findCase(position().getPositionAt(direction(), currentSpeed));
*/

    position().moveAt(direction(), currentSpeed);

/*    if(next == actualCase->position())
        return;

    next.toPixels();

    switch (direction()) {
        case Direction::UP:

            if (position().y() < next.y()) {
                position().y() = next.y();
            }

            break;
        case Direction::DOWN:

            if (position().y() > next.y()) {
                position().y() = next.y();
            }

            break;
        case Direction::LEFT:

            if (position().x() < next.x()) {
                position().x() = next.x();
            }

            break;
        case Direction::RIGHT:
            if (position().x() > next.x()) {
                position().x() = next.x();
            }
            break;
    }*/

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

void Ghost::handleHomeMode() noexcept {
    // Home mode: ghost going up & down
    if(Board::isCase(position())) {

        auto const &nextCase = board().getBoardCaseAtPixels(position(), direction());

        if (!nextCase) return; // should not be null

        if (!BoardCase::isPracticable(nextCase.value())) {
            if (direction() == Direction::DOWN) {
                direction() = Direction::UP;
            } else if (direction() == Direction::UP) {
                direction() = Direction::DOWN;
            }

            Ghost::changeAnimation();
        }
    }

    position().moveAt(direction(), speed());
}

void Ghost::startHomeMode() noexcept {
    if(ghostMode() == GhostMode::Home) return;
    reset();
}