#include "entities/ghosts/clyde.h"

using namespace pacman;

void Clyde::tick() noexcept {
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
        case GhostMode::Frightened:
            break;
        case GhostMode::Eaten:
            break;
    }

    // handle path finding & movements
    handleMovement();
}

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
    Ghost::changeAnimation();
}
