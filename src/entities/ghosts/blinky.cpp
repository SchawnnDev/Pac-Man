#include "entities/ghosts/blinky.h"

using namespace pacman;

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

void Blinky::handleChaseTarget() noexcept {
    if (ghostMode() != GhostMode::Chase) return;
    target() = Board::findCase(pacman().position());
}

void Blinky::handleHomeMode() noexcept {}

void Blinky::startHomeMode() noexcept {

}