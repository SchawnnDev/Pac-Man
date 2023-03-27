#pragma once

#include <cstdint>

#include "level.h"
#include "utils/constants.h"

namespace pacman {

/**
 * @class GameClass
 * @brief Handles the ghosts scatter and chase mode durations
 */
    class GameCycle {

        int m_cycle;
        uint64_t m_startTicks;

    public:

        /**
        * @brief Default constructor for GameCycle.
        */
        GameCycle() : m_cycle{1}, m_startTicks{0} {}

        /**
         * @brief Increments the current game cycle.
         */
        constexpr void changeGameState() { m_cycle++; }

        /**
         * @brief Gets the duration of the cycle for the specified level.
         * @param p_level The level for which to get the cycle duration.
         * @return The duration of the cycle.
         */
        [[nodiscard]] constexpr uint64_t getCycleDuration(int p_level) const {

            auto cycle = (m_cycle > CYCLES_COUNT ? CYCLES_COUNT : m_cycle) - 1;

            if (p_level == 1) {
                return m_startTicks + START_CYCLES[cycle];
            } else if (p_level >= 2 && p_level <= 4) {
                return m_startTicks + MID_CYCLES[cycle];
            } else {
                return m_startTicks + END_CYCLES[cycle];
            }
        }

        /**
         * @brief Resets the current game cycle to zero.
         */
        constexpr void reset() { m_cycle = 1; m_startTicks = 0; }

        /**
         * @return Reference to start ticks of cycle
         */
        [[nodiscard]] auto &startTicks() { return m_startTicks; }

        /**
         * @return LevelState according to current cycle
         */
        [[nodiscard]] auto getGameState() const { return m_cycle % 2 == 0 ? LevelState::Chase : LevelState::Scatter; }
    };

}