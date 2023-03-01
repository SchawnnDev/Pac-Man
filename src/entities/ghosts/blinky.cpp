#include "entities/ghosts/blinky.h"

void Blinky::tick() noexcept {

    if (ghostMode() == GhostMode::Scatter) {

        // On position
        if (!Board::isCase(position())) {
            position().moveAt(direction(), speed());
        } else {

            // Ghost is on a tile, and he must choose a direction
            auto actualCase = board().getBoardCaseAtPixels(position());
            auto frontCase = board().getBoardCaseAtPixels(position(), direction());
            auto leftDirection = getDirectionByAngle(direction(), 90);
            auto leftCase = board().getBoardCaseAtPixels(position(), leftDirection);
            auto rightDirection = getDirectionByAngle(direction(), -90);
            auto rightCase = board().getBoardCaseAtPixels(position(), rightDirection);

            // actualCase cannot be null
            if (actualCase) {
                auto foundCase = getClosestBoardCase(target(),
                                                     std::make_pair(direction(), frontCase),
                                                     std::make_pair(leftDirection, leftCase),
                                                     std::make_pair(rightDirection, rightCase)
                );

                // foundCase should not be null
                if (foundCase.second) {
                    move(foundCase.first);
                    position().moveAt(direction(), speed());
                }

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
    ghostMode() = GhostMode::Scatter;
    target() = {BOARD_SIZE_X - 3, -3};
}

void Blinky::startChaseMode() noexcept {

}

Blinky::~Blinky() = default;
