#include "entities/ghosts/blinky.h"

using namespace pacman;

void Blinky::tick() noexcept {
    if(freezed() || !activated()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

    switch(ghostMode())
    {
        case GhostMode::Home:
            break;
        case GhostMode::Scatter:
            handleScatterMode();
            break;
        case GhostMode::Chase:
            handleChaseTarget();
            break;
        case GhostMode::Frightened:
            break;
        case GhostMode::Eaten:
            break;
    }

    // handle path finding & movements
    handleMovement();
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

void Blinky::handleChaseTarget() noexcept {
    if (ghostMode() != GhostMode::Chase) return;
    target() = Board::findCase(pacman().position());
}

void Blinky::reset() noexcept
{
    position() = getPosition(10, 10);
    direction() = Direction::LEFT;
    startScatterMode();
    Ghost::changeAnimation();
}
