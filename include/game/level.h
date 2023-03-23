#pragma once

#include "utils/constants.h"

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

    static constexpr int getFruitValueByLevel(int p_level)
    {
        auto const idx = (p_level > FRUITS_REGISTERED ? FRUITS_REGISTERED : p_level) - 1;
        return FRUIT_VALUES[idx];
    }

}