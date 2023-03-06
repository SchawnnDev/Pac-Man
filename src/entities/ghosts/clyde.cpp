#include "entities/ghosts/clyde.h"

using namespace pacman;

void Clyde::tick() noexcept {
    if(freezed()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

    // handle path finding & movements
    handleMovement();
}

void Clyde::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {0, BOARD_SIZE_Y + 1};
}

void Clyde::startChaseMode() noexcept {
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
}

void Clyde::handleChaseTarget() noexcept {
    if (ghostMode() != GhostMode::Chase) return;

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

void Clyde::handleHomeMode() noexcept {}