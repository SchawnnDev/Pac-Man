#pragma once

namespace pacman {

    /**
     * @brief Represents the global state of the game
     * - LoadingScreen: Waiting for credit display
     * - Playing: Game display
     * - GameOver: Game display with game over animation
     * - End: Game end animation
     */
    enum class GameState {
        LoadingScreen,
        Playing,
        GameOver,
        End
    };
}