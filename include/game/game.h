#pragma once

#include <optional>
#include "board/board.h"
#include "entities/entity.h"
#include "entities/pacman.h"
#include "entities/ghosts/blinky.h"
#include "sprites/sprite-handler.h"
#include "entities/ghosts/clyde.h"
#include "entities/ghosts/pinky.h"
#include "entities/ghosts/inky.h"
#include "utils/clock.h"
#include "screens/loading-screen.h"
#include "utils/shared_value.h"
#include "screens/header-screen.h"
#include "screens/footer-screen.h"
#include "screens/game-screen.h"
#include "level.h"
#include "game-state.h"
#include "player.h"

namespace pacman {

    class Game {
        // Game logic
        int64_t m_ticks;
        shared_value<GameState> m_state;
        shared_value<LevelState> m_levelState;
        shared_value<int> m_credit;
        shared_value<int> m_highScore;
        shared_value<int> m_playerCount;
        std::array<PlayerPtr, 2> m_players;
        PlayerPtr m_currentPlayer;
        int64_t m_freezeTimeout;
        int m_eatenFrightenedGhosts;

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

        [[nodiscard]] GameState gameState() const noexcept { return m_state; }

        GameState &gameState() noexcept { return m_state; }

        [[nodiscard]] Pacman const &pacman() const noexcept { return m_pacman; }

        Pacman &pacman() noexcept { return m_pacman; }

        [[nodiscard]] Board const &board() const noexcept { return m_board; }

        Board &board() noexcept { return m_board; }

        [[nodiscard]] shared_value<int> credit() const noexcept { return m_credit; }

        void start() noexcept;

        void end() noexcept;

        void handleEvents() noexcept;

        void handleKeys() noexcept;

        void handleSpecialKeys(SDL_Event const& event) noexcept;

        void handleLogic() noexcept;

        void handleTicks() noexcept;

        void handleDrawing() noexcept;

        void updateCredits(int p_credits) noexcept;

        void updateScore(int p_scoreToAdd) noexcept;

        void updateHighScore(int p_highScore) noexcept;

        void startPlaying(int p_players) noexcept;

        void startLevel(bool p_died) noexcept;

        void endLevel() noexcept;

        void startScatter() noexcept;

        void startChase() noexcept;

        void startFrightened() noexcept;

        void checkCollisions() noexcept;

        void freezeDisplayScore(Entity& p_which, int p_score) noexcept;

        void performPacmanDying() noexcept;

        int calculateFrightenedGhostScore() noexcept;

        void endPlaying() noexcept;

        void freezeEntities() noexcept;

        void unfreezeEntities() noexcept;
    };

}
