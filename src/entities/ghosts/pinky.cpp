#include "entities/ghosts/pinky.h"

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

void Pinky::handleChaseTarget(std::span<const Entity> p_targets) noexcept {
    if (ghostMode() != GhostMode::Chase || p_targets.size()) return;

    auto position = Board::findCase(p_pacman.position());
    // move 4 cases in the front of blinky
    position.moveAt(p_pacman.direction(), 4);

    // move 4 cases to the left if pacman is going up (specific)
    if (p_pacman.direction() == Direction::UP) {
        position.moveAt(Direction::LEFT, 4);
    }

    target() = position;
}

void Pinky::handleHomeMode() noexcept {}