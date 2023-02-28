#pragma once

#include "sprite-animation.h"

enum class BoardCaseType {
    PointPath,
    BasicPath,
    Bonus,
    Wall,
    GhostHome,
    GhostHomeDoorLeft,
    GhostHomeDoorRight,
    GhostHomeDoor,
    DoorLeft,
    DoorRight,
    Nothing
};

class BoardCase {
    int m_x;
    int m_y;
    BoardCaseType m_type;
    std::optional<SpriteAnimation> m_animation;
public:
    BoardCase() : m_x(0), m_y(0), m_type(BoardCaseType::PointPath) {}

    ~BoardCase();

    BoardCase(const int &p_x, const int &p_y, const BoardCaseType &p_type,
              const std::optional<SpriteAnimation> &p_animation) : m_x(p_x), m_y(p_y), m_type(p_type),
                                                                     m_animation(p_animation) {}

    [[nodiscard]] constexpr int const& x() const { return m_x; };

    constexpr int &x() { return m_x; };

    [[nodiscard]] constexpr int const& y() const { return m_y; };

    constexpr int &y() { return m_y; };

    [[nodiscard]] const BoardCaseType& type() const { return m_type; };

    BoardCaseType &type() { return m_type; };

    [[nodiscard]] std::optional<SpriteAnimation> const& animation() const { return m_animation; };

    std::optional<SpriteAnimation> &animation() { return m_animation; };

    static inline bool isPracticable(BoardCase p_boardCase)
    {
        return p_boardCase.type() == BoardCaseType::PointPath
               || p_boardCase.type() == BoardCaseType::BasicPath
               || p_boardCase.type() == BoardCaseType::Bonus
               || p_boardCase.type() == BoardCaseType::DoorLeft
               || p_boardCase.type() == BoardCaseType::DoorRight;
    }
};