#pragma once

#include <memory>

namespace pacman {

    /**
     * @brief Represents a player of pacman, containing all infos about a single player
     */
    class Player {
        int m_id;
        int m_score;
        int m_level;
        int m_lives;
        int m_eatenFruitsCurrentLevel;
        int m_eatenPowerPelletsCurrentLevel;
        bool m_extraLifeGiven;
        bool m_deadCurrentLevel; // Player has died once in the current level
        std::unordered_map<size_t, bool> m_map;
    public:
        explicit Player(int p_id) : m_id{p_id}, m_score{0}, m_level{1}, m_lives{3},
                                    m_eatenFruitsCurrentLevel{0}, m_eatenPowerPelletsCurrentLevel{0},
                                    m_extraLifeGiven{false}, m_deadCurrentLevel{false}, m_map{} {}

        int &id() { return m_id; }
        int &score() { return m_score; }
        int &level() { return m_level; }
        int &lives() { return m_lives; }
        int &eatenFruitsCurrentLevel() { return m_eatenFruitsCurrentLevel; }
        int &eatenPowerPelletsCurrentLevel() { return m_eatenPowerPelletsCurrentLevel; }
        bool &deadCurrentLevel() { return m_deadCurrentLevel; }
        auto &map() { return m_map; }

        /**
         * @brief Returns the player ID.
         * @return The player ID.
         */
        [[nodiscard]] int id() const { return m_id; }

        /**
         * @brief Returns the player's score.
         * @return The player's score.
         */
        [[nodiscard]] int score() const { return m_score; }

        /**
         * @brief Returns the current level of the game the player is on.
         * @return The current level of the game the player is on.
         */
        [[nodiscard]] int level() const { return m_level; }

        /**
         * @brief Returns the number of lives the player has remaining.
         * @return The number of lives the player has remaining.
         */
        [[nodiscard]] int lives() const { return m_lives; }

        /**
         * @brief Returns the number of fruits the pacman has eaten in the current level.
         * @return The number of fruits the pacman has eaten in the current level.
         */
        [[nodiscard]] int eatenFruitsCurrentLevel() const { return m_eatenFruitsCurrentLevel; }

        /**
         * @brief Returns the number of power pellets the pacman has eaten in the current level.
         *        (handle sirens)
         * @return The number of power pellets the pacman has eaten in the current level.
         */
        [[nodiscard]] int eatenPowerPelletsCurrentLevel() const { return m_eatenPowerPelletsCurrentLevel; }

        /**
         * @brief Returns whether the player has been given an extra life.
         * @return True if the player has been given an extra life, false otherwise.
         */
        [[nodiscard]] bool extraLifeGiven() const { return m_extraLifeGiven; }

        /**
         * @brief Returns whether the player has died in the current level.
         * @return True if the player has died in the current level, false otherwise.
         */
        [[nodiscard]] bool deadCurrentLevel() const { return m_deadCurrentLevel; }

        /**
         * @brief Returns a const reference to the map of collected items.
         * @return A const reference to the map of collected items.
         */
        [[nodiscard]] auto map() const { return m_map; }

       /**
        * @brief Gives the player an extra life if one has not already been given.
        */
        inline void giveExtraLife() {
            if (m_extraLifeGiven) return;
            m_lives++;
            m_extraLifeGiven = true;
        }

        /**
         * @brief Resets all the member variables of the Player object to their initial values.
         */
        inline void reset() {
            m_score = 0;
            m_level = 1;
            m_lives = 3;
            m_eatenFruitsCurrentLevel = 0;
            m_eatenPowerPelletsCurrentLevel = 0;
            m_extraLifeGiven = false;
            m_map.clear();
        }

        /**
         * @brief Advances the player to the next level.
         */
        inline void nextLevel() {
            m_level++;
            m_eatenFruitsCurrentLevel = 0;
            m_eatenPowerPelletsCurrentLevel = 0;
            m_deadCurrentLevel = false;
            m_map.clear();
        }
    };

    using PlayerPtr = std::shared_ptr<Player>;

}