#pragma once

#include <optional>
#include "board/board.h"
#include "entities/entity.h"

enum class GameState {
    Idle,
    Starting
};

class Game {
    Board m_board;
    std::vector<std::shared_ptr<Entity>> m_entities;
    GameState m_state;
public:
    Game() = default;
    ~Game() = default;

    void start();

    void end();

    [[nodiscard]] const GameState &gameState() const { return m_state; };
    GameState &gameState() { return m_state; };

};

void Game::start() {

}

void Game::end() {

}
