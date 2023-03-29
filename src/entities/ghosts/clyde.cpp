#include "entities/ghosts/clyde.h"

using namespace pacman;

void Clyde::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {0, BOARD_SIZE_Y + 1};
}

void Clyde::handleChaseTarget() noexcept {
    auto currentPosition = Board::findCase(position());
    auto position = Board::findCase(pacman().position());

    if(position.distanceTo(currentPosition) >= 64) // distance without sqrt => 8^2
    {
        target() = position;
    } else {
        // Clyde switches to scatter when pacman is located at 8 or more cases
        target() = {0, BOARD_SIZE_Y + 1};
    }

}

void Clyde::reset() noexcept
{
    position() = getPosition(11, 13);
    ghostMode() = GhostMode::Home;
    direction() = Direction::UP;
    frightened() = false;
    ticks() = 0;
    Ghost::changeAnimation();
}
