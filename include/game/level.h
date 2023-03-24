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

    /**
     * @param p_levelState Actual level state
     * @return If p_levelState is a playing state or not
     */
    static constexpr bool isLevelPlaying(LevelState p_levelState) {
        return p_levelState == LevelState::Chase || p_levelState == LevelState::Scatter;
    }

    /**
     * @param p_level Fruit level to get
     * @return Fruit representing the given level
     */
    static constexpr int getFruitValueByLevel(int p_level)
    {
        auto const idx = (p_level > FRUITS_REGISTERED ? FRUITS_REGISTERED : p_level) - 1;
        return FRUIT_VALUES[idx];
    }

}