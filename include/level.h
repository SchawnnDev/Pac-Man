#pragma once

namespace pacman {

    // All in global state or new level state?
    enum class LevelState {
        PlayerDisplay,
        Ready,
        Scatter,
        Chase,
        End
    };

    static constexpr bool isLevelPlaying(LevelState p_levelState) {
        return p_levelState == LevelState::Chase || p_levelState == LevelState::Scatter;
    }

}