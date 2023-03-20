#include "entities/ghosts/inky.h"

using namespace pacman;

void Inky::tick() noexcept {
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

void Inky::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {BOARD_SIZE_X - 1, BOARD_SIZE_Y + 1};
    turnAround();
}

void Inky::handleChaseTarget() noexcept {
    auto position = Board::findCase(pacman().position());
    // move 2 cases in the front of pacman
    position.moveAt(pacman().direction(), 2);

    // move 2 cases to the left if pacman is going up (specific)
    if (pacman().direction() == Direction::UP) {
        position.moveAt(Direction::LEFT, 2);
    }

    // Calculate the vector between above point and blinky's position
    // Rotate vec2 by 180 degrees (just switch signs)
    target() = Board::findCase(m_blinky.position()).rotateVec(position, 180);
}

void Inky::reset() noexcept
{
    position() = getPosition(9, 13);
    ghostMode() = GhostMode::Home;
    direction() = Direction::UP;
    target() = {9, 11};
    frightened() = false;
    Ghost::changeAnimation();
}
