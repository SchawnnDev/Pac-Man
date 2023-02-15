#pragma once

#include <optional>
#include "board/board.h"
#include "entities/entity.h"

enum class GameState {
    WaitingStart,
    Idle,
    Starting,
    End
};

class Game {
    Board m_board;
    std::vector<std::shared_ptr<Entity>> m_entities;
    GameState m_state;
    SDL_Window* m_window;
    SDL_Renderer* m_windowRenderer;
    SDL_Surface* m_spriteSurface;
public:
    Game();
    ~Game();

    void start();

    void end();

    void handleEvents();

    void handleKeys();

    [[nodiscard]] const GameState &gameState() const { return m_state; };
    GameState &gameState() { return m_state; };

    std::vector<std::shared_ptr<Entity>> getEntitiesByType(EntityType p_entityType);

};
