#include "entities/ghosts/pinky.h"

using namespace pacman;

void Pinky::tick() noexcept {
    if(freezed()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

    // handle path finding & movements
    handleMovement();
}

void Pinky::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;
    target() = {2, -3};
}

void Pinky::startChaseMode() noexcept {
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
}

void Pinky::handleChaseTarget() noexcept {
    if (ghostMode() != GhostMode::Chase) return;

    auto position = Board::findCase(pacman().position());
    // move 4 cases in the front of pacman
    position.moveAt(pacman().direction(), 4);

    // move 4 cases to the left if pacman is going up (specific)
    if (pacman().direction() == Direction::UP) {
        position.moveAt(Direction::LEFT, 4);
    }

    target() = position;
}

void Pinky::handleHomeMode() noexcept {}

void Pinky::startHomeMode() noexcept {
    if(ghostMode() == GhostMode::Home) return;
    direction() = Direction::UP;
    position() = {10, 13};

}
