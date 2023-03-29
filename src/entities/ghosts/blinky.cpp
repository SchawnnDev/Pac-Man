#include "entities/ghosts/blinky.h"

using namespace pacman;

void Blinky::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {BOARD_SIZE_X - 3, -3};
}

void Blinky::handleChaseTarget() noexcept {
    if (ghostMode() != GhostMode::Chase) return;
    target() = Board::findCase(pacman().position());
}

void Blinky::reset() noexcept
{
    Ghost::reset();
    position() = getPosition(10, 10);
    direction() = Direction::LEFT;
    startScatterMode();
    Ghost::changeAnimation();
}
