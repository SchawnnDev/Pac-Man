#pragma once

#include "utils/constants.h"

/**
 * @class GameClass
 * @brief Handles the ghosts scatter and chase mode durations
 */
class GameCycle {

    int m_cycle;

public:

    /**
    * @brief Default constructor for GameCycle.
    */
    GameCycle() : m_cycle{0} {}

    /**
     * @brief Increments the current game cycle.
     */
    constexpr void changeGameState() { m_cycle++; }

    /**
     * @brief Gets the duration of the cycle for the specified level.
     * @param p_level The level for which to get the cycle duration.
     * @return The duration of the cycle.
     */
    constexpr int getCycleDuration(int p_level) const {

        auto cycle = (m_cycle > CYCLES_COUNT ? CYCLES_COUNT : m_cycle) - 1;

        if(p_level == 1) {
            return START_CYCLES[cycle];
        } else if(p_level >= 2 && p_level <= 4) {
            return MID_CYCLES[cycle];
        } else {
            return END_CYCLES[cycle];
        }
    }

    /**
     * @brief Resets the current game cycle to zero.
     */
    constexpr void reset() { m_cycle = 0; }

};