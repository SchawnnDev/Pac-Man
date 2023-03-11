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
#include "utils/shared_value.h"
#include "screens/header-screen.h"
#include "screens/footer-screen.h"
#include "screens/game-screen.h"

namespace pacman {

    // Global state
    enum class GameState {
        LoadingScreen,
        Playing,
        GameOver,
        End
    };
    // All in global state or new level state?
    enum class LevelState {
        PlayerDisplay,
        Ready,
        Running,
        End
    };

    class Game {
        // Game logic
        int m_level;
        GameState m_state;
        LevelState m_levelState;
        shared_value<int> m_credit;
        shared_value<int> m_highScore;
        std::array<shared_value<int>, 2> m_scores;
        int m_players;
        shared_value<int> m_currentPlayer;

        // Handlers
        SpriteHandler m_spriteHandler;
        Board m_board;

        // Entities
        Pacman m_pacman;
        Blinky m_blinky;
        Clyde m_clyde;
        Pinky m_pinky;
        Inky m_inky;

        // Screens
        LoadingScreen m_loadingScreen;
        HeaderScreen m_headerScreen;
        FooterScreen m_footerScreen;
        GameScreen m_gameScreen;

        // SDL
        std::unique_ptr<SDL_Window,
                decltype(&SDL_DestroyWindow)> m_window{nullptr, SDL_DestroyWindow};
        std::unique_ptr<SDL_Renderer,
                decltype(&SDL_DestroyRenderer)> m_windowRenderer{nullptr, SDL_DestroyRenderer};
        std::unique_ptr<SDL_Surface,
                decltype(&SDL_FreeSurface)> m_spriteSurface{nullptr, SDL_FreeSurface};
        SDL_Texture *m_spriteTexture;

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

        [[nodiscard]] shared_value<int> credit() const { return m_credit; }

        void start();

        void end();

        void handleEvents();

        void handleKeys();

        void handleSpecialKeys(SDL_Event const& event);

        void handleLogic();

        void handleDrawing();

        void updateCredits(int p_credits);

        void updateHighScore(int p_highScore);

        void startPlaying(int p_players);
    };

}
