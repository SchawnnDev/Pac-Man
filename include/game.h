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
#include "screens/loading-screen.h"

namespace pacman {

    enum class GameState {
        LoadingScreen,
        PlayerSelect,
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
        Pacman m_pacman;
        Blinky m_blinky;
        Clyde m_clyde;
        Pinky m_pinky;
        Inky m_inky;

        // Screens
        LoadingScreen m_loadingScreen;

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
        int m_credits;
    public:
        Game();

        ~Game();

        [[nodiscard]] GameState gameState() const { return m_state; }

        GameState &gameState() { return m_state; }

        [[nodiscard]] Pacman const &pacman() const { return m_pacman; }

        Pacman &pacman() { return m_pacman; }

        [[nodiscard]] Board const &board() const { return m_board; }

        Board &board() { return m_board; }

        [[nodiscard]] int level() const { return m_level; }

        int &level() { return m_level; }

        [[nodiscard]] int credits() const { return m_credits; }

        void start();

        void end();

        void handleEvents();

        void handleKeys();

        void handleLogic();

        void handleDrawing();

        void updateCredits(int p_credits);
    };

}
