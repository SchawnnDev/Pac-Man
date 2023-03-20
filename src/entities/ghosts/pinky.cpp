#include "entities/ghosts/pinky.h"

using namespace pacman;

void Pinky::tick() noexcept {
    if(freezed() || !activated()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

    switch(ghostMode())
    {
        case GhostMode::Home:
            handleHomeMode();
            return;
        case GhostMode::Scatter:
            handleScatterMode();
            break;
        case GhostMode::Chase:
            handleChaseTarget();
            break;
        case GhostMode::Eaten:
            handleEatenMode();
            break;
    }

    // handle path finding & movements
    handleMovement();
}

void Pinky::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {2, -3};
}

void Pinky::handleChaseTarget() noexcept {
    auto position = Board::findCase(pacman().position());
    // move 4 cases in the front of pacman
    position.moveAt(pacman().direction(), 4);

    // move 4 cases to the left if pacman is going up (specific)
    if (pacman().direction() == Direction::UP) {
        position.moveAt(Direction::LEFT, 4);
    }

    target() = position;
}

void Pinky::reset() noexcept
{
    position() = getPosition(10, 12);
    ghostMode() = GhostMode::Home;
    direction() = Direction::DOWN;
    target() = {10, 14};
    frightened() = false;
    Ghost::changeAnimation();
}
