#pragma once

#include <optional>
#include "board/board.h"
#include "entities/entity.h"
#include "entities/pacman.h"
#include "entities/ghosts/blinky.h"
#include "sprite-handler.h"
#include "entities/ghosts/clyde.h"
#include "entities/ghosts/pinky.h"
#include "entities/ghosts/inky.h"
#include "utils/clock.h"

namespace pacman {

    enum class GameState {
        WaitingStart,
        Idle,
        Starting,
        End
    };

    class Game {
        SpriteHandler m_spriteHandler;
        Board m_board;
        GameState m_state;

        // Entities
        Pacman m_pacMan;
        Blinky m_blinky;
        Clyde m_clyde;
        Pinky m_pinky;
        Inky m_inky;

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

        // Game logic
        int m_level;
    public:
        Game();

        ~Game();

/*    Game(Game const&) = delete;
    Game& operator=(Game const&) = delete;*/

        void start();

        void end();

        void handleEvents();

        void handleKeys();

        [[nodiscard]] GameState gameState() const { return m_state; }

        GameState &gameState() { return m_state; }

        [[nodiscard]] Pacman const &pacman() const { return m_pacMan; }

        Pacman &pacman() { return m_pacMan; }

        [[nodiscard]] Board const &board() const { return m_board; }

        Board &board() { return m_board; }

        [[nodiscard]] int level() const { return m_level; }

        int &level() { return m_level; }

        void handleLogic();

        void handleDrawing();
    };

}
