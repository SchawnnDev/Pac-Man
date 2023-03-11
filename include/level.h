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

}