#pragma once

#include <optional>

#include "board/board.h"
#include "entities/entity.h"
#include "entities/pacman.h"
#include "entities/fruit.h"
#include "screens/loading-screen.h"
#include "screens/header-screen.h"
#include "screens/footer-screen.h"
#include "screens/game-screen.h"
#include "sprites/sprite-handler.h"
#include "level.h"
#include "game-state.h"
#include "player.h"
#include "game-cycle.h"
#include "utils/clock.h"
#include "utils/shared_value.h"
#include "audio/audio-handler.h"
#include "entities/ghost.h"

namespace pacman {

    /**
     * @class Game
     * @brief The main class that handles the game logic, rendering, and input handling.
     */
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
        bool m_currentEatSound;

        // Handlers
        SpriteHandler m_spriteHandler;
        Board m_board;
        GameCycle m_gameCycle;
        AudioHandler m_audioHandler;

        // Entities
        Pacman m_pacman;
        Ghost<EntityType::Blinky> m_blinky;
        Ghost<EntityType::Clyde> m_clyde;
        Ghost<EntityType::Pinky> m_pinky;
        Ghost<EntityType::Inky> m_inky;
        Fruit m_fruit;

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
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_spriteTexture{nullptr, SDL_DestroyTexture};

    protected:
        /**
         * @brief Handles all the SDL events.
         */
        void handleEvents() noexcept;

        /**
         * @brief Handles the input keys.
         */
        void handleKeys() noexcept;

        /**
         * @brief Handles the special input keys.
         * @param event The SDL event.
         */
        void handleSpecialKeys(SDL_Event const& event) noexcept;

        /**
         * @brief Handle game logic.
         *
         * This method updates the game state, such as the position of entities, based on the elapsed time and the current state.
         * It also checks for collisions and performs actions based on the current state.
         */
        void handleLogic() noexcept;

        /**
         * @brief Handle audios
         *
         * This method checks the game/level state, and updates the audio when a specific state changes
         */
        void handleAudio() noexcept;

        /**
         * @brief Handle game ticks.
         *
         * This method updates the game tick count and resets it if necessary.
         */
        void handleTicks() noexcept;

        /**
         * @brief Handle game drawing.
         *
         * This method draws the game screen using the SDL_Renderer.
         */
        void handleDrawing() noexcept;

        /**
         * @brief Update the number of credits.
         *
         * @param p_credits The new number of credits.
         */
        void updateCredits(int p_credits) noexcept;

        /**
         * @brief Update the score of the current player.
         *
         * @param p_scoreToAdd The score to add to the current score.
         */
        void updateScore(int p_scoreToAdd) noexcept;

        /**
         * @brief Update the high score.
         *
         * @param p_highScore The new high score.
         */
        void updateHighScore(int p_highScore) noexcept;

        /**
         * @brief Start playing the game.
         *
         * @param p_players The number of players (1 or 2).
         */
        void startPlaying(int p_players) noexcept;

        /**
         * @brief Start a new level.
         *
         * @param p_died True if the current player died in the previous level.
         */
        void startLevel(bool p_died) noexcept;

        /**
         * @brief End the current level.
         */
        void endLevel() noexcept;

        /**
         * @brief Start the scatter mode for the ghosts.
         */
        void startScatter() noexcept;

        /**
         * @brief Start the chase mode for the ghosts.
         */
        void startChase() noexcept;

        /**
         * @brief Start the frightened mode for the ghosts.
         */
        void startFrightened() noexcept;

        /**
         * @brief Check for collisions between entities.
         */
        void checkCollisions() noexcept;

        /**
         * @brief Display the score and freeze the given entity.
         *
         * @param p_which The entity to freeze.
         * @param p_score The score to display.
         */
        void freezeDisplayScore(Entity& p_which, int p_score) noexcept;

        /**
         * @brief Perform the dying sequence for Pacman.
         */
        void performPacmanDying() noexcept;

        /**
         * @brief Calculate the score to add when a frightened ghost is eaten.
         *
         * @return The score to add.
         */
        int calculateFrightenedGhostScore() noexcept;

        /**
         * @brief End playing the game.
         */
        void endPlaying() noexcept;

        /**
         * @brief Freeze all entities in the game.
         *
         */
        void freezeEntities() noexcept;

        /**
         * @brief Unfreeze all entities in the game.
         *
         */
        void unfreezeEntities() noexcept;

        /**
         * @brief Check cycle change and do actions if a change occurs
         */
        void handleCycleChange() noexcept;

        /**
         * Handle ghost mode, exit, ghost counters etc
         */
        void handleGhostHomePriority() noexcept;
    public:
        /**
         * @brief Constructs a new Game object.
         *
         */
        Game();

        /**
         * @brief Destroys the Game object.
         *
         */
        ~Game();

        /**
         * @brief Starts the game loop.
         *
         */
        void start() noexcept;

        /**
         * @brief Ends the game loop and exits the game.
         *
         */
        void end() noexcept;

    };

}
