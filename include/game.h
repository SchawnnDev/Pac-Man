#pragma once

#include <optional>
#include "board/board.h"
#include "entities/entity.h"
#include "entities/pacman.h"
#include "entities/ghosts/blinky.h"

enum class GameState {
    WaitingStart,
    Idle,
    Starting,
    End
};

class Game {
    Board m_board;
    GameState m_state;

    // Entities
    Pacman m_pacMan;
    Blinky m_blinky;

    // SDL
    SDL_Window* m_window;
    SDL_Renderer* m_windowRenderer;
    SDL_Surface* m_spriteSurface;
    SDL_Texture* m_spriteTexture;
public:
    Game();
    ~Game();

    void start();

    void end();

    void handleEvents();

    void handleKeys();

    [[nodiscard]] const GameState &gameState() const { return m_state; };
    GameState &gameState() { return m_state; };

    void handleLogic();

    void handleDrawing();
};
