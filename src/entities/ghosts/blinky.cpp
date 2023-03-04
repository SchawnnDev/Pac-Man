#include "entities/ghosts/blinky.h"

void Blinky::tick() noexcept {
    if(freezed()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

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

void Blinky::handleChaseTarget(std::span<const Entity> p_targets) noexcept {
    if (ghostMode() != GhostMode::Chase || p_targets.size() == 0) return;
    target() = Board::findCase(p_targets..position());
}

void Blinky::handleHomeMode() noexcept {}