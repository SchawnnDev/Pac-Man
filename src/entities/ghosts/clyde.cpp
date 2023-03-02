#include "entities/ghosts/clyde.h"

void Clyde::tick() noexcept {
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

void Clyde::handleChaseTarget(const Entity &p_pacman) noexcept {
    if (ghostMode() != GhostMode::Chase) return;

    auto currentPosition = Board::findCase(position());
    auto position = Board::findCase(p_pacman.position());

    if(position.distanceTo(currentPosition) >= 64) // distance without sqrt => 8^2
    {
        target() = p_pacman.position();
    } else {
        // Clyde switches to scatter when pacman is located at 8 or more cases
        target() = {0, BOARD_SIZE_Y + 1};
    }

}

void Clyde::handleHomeMode() noexcept {}