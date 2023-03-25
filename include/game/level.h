#pragma once

#include "utils/constants.h"

namespace pacman {

    /**
     * @brief Level state
     * According to GameState, the LevelState represents a sub-state to GameState::Playing
     * The 5 states are:
     * - PlayerDisplay: Current player displayed, entities not drawn
     * - Ready: Ready text displayed, entities drawn
     * - Scatter: Scatter mode for ghosts
     * - Chase: Chase mode for ghosts
     * - End: End of level, leading to a new level
     */
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