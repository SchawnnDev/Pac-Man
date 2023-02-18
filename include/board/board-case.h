#pragma once

#include "../sprite-animation.h"

enum class BoardCaseType {
    PointPath,
    BasicPath,
    Bonus,
    Wall,
    GhostHome,
    GhostHomeDoorLeft,
    GhostHomeDoorRight,
    GhostHomeDoor,
    Nothing
};

class BoardCase {
    int m_x;
    int m_y;
    BoardCaseType m_type;
    std::shared_ptr<SpriteAnimation> m_animation;
public:
    BoardCase() : m_x(0), m_y(0), m_type(BoardCaseType::PointPath) {}

    ~BoardCase();

    BoardCase(const int &p_x, const int &p_y, const BoardCaseType &p_type,
              const std::shared_ptr<SpriteAnimation> &p_animation) : m_x(p_x), m_y(p_y), m_type(p_type),
                                                                     m_animation(p_animation) {}

    [[nodiscard]] const int &x() const { return m_x; };

    int &x() { return m_x; };

    [[nodiscard]] const int &y() const { return m_y; };

    int &y() { return m_y; };

    [[nodiscard]] const BoardCaseType &type() const { return m_type; };

    BoardCaseType &type() { return m_type; };

    [[nodiscard]] const std::shared_ptr<SpriteAnimation> &animation() const { return m_animation; };

    std::shared_ptr<SpriteAnimation> &animation() { return m_animation; };

    static inline bool isPracticable(BoardCase p_boardCase)
    {
        return p_boardCase.type() == BoardCaseType::PointPath
               || p_boardCase.type() == BoardCaseType::BasicPath
               || p_boardCase.type() == BoardCaseType::Bonus;
    }
};