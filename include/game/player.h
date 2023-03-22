#pragma once

#include <memory>

namespace pacman {

    class Player {
        int m_id;
        int m_score;
        int m_level;
        int m_lives;
        bool m_extraLifeGiven;
    public:
        explicit Player(int p_id) : m_id{p_id}, m_score{0}, m_level{1}, m_lives{3}, m_extraLifeGiven{false} {}

        int &id() { return m_id; }
        int &score() { return m_score; }
        int &level() { return m_level; }
        int &lives() { return m_lives; }

        [[nodiscard]] int id() const { return m_id; }
        [[nodiscard]] int score() const { return m_score; }
        [[nodiscard]] int level() const { return m_level; }
        [[nodiscard]] int lives() const { return m_lives; }
        [[nodiscard]] bool extraLifeGiven() const { return m_extraLifeGiven; }

        inline void giveExtraLife() { m_lives++; m_extraLifeGiven = true; }

        inline void reset() {
            m_score = 0;
            m_level = 1;
            m_lives = 1;
            m_extraLifeGiven = false;
        }
    };

    using PlayerPtr = std::shared_ptr<Player>;

}