#pragma once

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
public:
    BoardCase() = default;
    ~BoardCase();
    BoardCase(const int &p_x, const int &p_y, const BoardCaseType &p_type) : m_x(p_x), m_y(p_y), m_type(p_type) {}

    [[nodiscard]] const int& x() const { return m_x; };
    int& x() { return m_x; };

    [[nodiscard]] const int& y() const { return m_y; };
    int& y() { return m_y; };

    [[nodiscard]] const BoardCaseType& type() const { return m_type; };
    BoardCaseType& type() { return m_type; };
};