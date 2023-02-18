#pragma once

#include <optional>
#include "board/board.h"
#include "entities/entity.h"
#include "entities/pacman.h"
#include "entities/ghosts/blinky.h"

enum class GameState
{
    WaitingStart,
    Idle,
    Starting,
    End
};

class Game
{
    std::shared_ptr<Board> m_board;
    GameState m_state;

    // Entities
    Pacman m_pacMan;
    Blinky m_blinky;

    // SDL
    std::unique_ptr<SDL_Window,
            decltype(&SDL_DestroyWindow)> m_window{nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer,
            decltype(&SDL_DestroyRenderer)> m_windowRenderer{nullptr,
                                                             SDL_DestroyRenderer};
    std::unique_ptr<SDL_Surface,
            decltype(&SDL_FreeSurface)> m_spriteSurface{nullptr,
                                                        SDL_FreeSurface};
    SDL_Texture *m_spriteTexture;
public:
    Game();

    ~Game();

    void start();

    void end();

    void handleEvents();

    void handleKeys();

    [[nodiscard]] const GameState &gameState() const
    { return m_state; };

    GameState &gameState()
    { return m_state; };

    void handleLogic();

    void handleDrawing();
};
