#include "entities/ghosts/inky.h"

void Inky::tick() noexcept {
    if(freezed()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

    // handle path finding & movements
    handleMovement();
}

void Inky::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {BOARD_SIZE_X - 1, BOARD_SIZE_Y + 1};
}

void Inky::startChaseMode() noexcept {
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
}

void Inky::handleChaseTarget(std::span<const Entity> p_targets) noexcept {
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

void Inky::handleHomeMode() noexcept {}