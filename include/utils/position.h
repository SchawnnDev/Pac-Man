#pragma once

#include "constants.h"
#include <SDL_rect.h>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Position {
    int m_x;
    int m_y;
public:

    Position() : m_x(0), m_y(0) {}
    ~Position();

    Position(int p_x, int p_y) : m_x(p_x), m_y(p_y) {}

    [[nodiscard]] const int &x() const { return m_x; };
    int &x() { return m_x; };

    [[nodiscard]] const int &y() const { return m_y; };
    int &y() { return m_y; };

};

inline SDL_Rect getPosition(int x, int y)
{
    return {x * BOARD_CASE_SIZE_WIDTH, y * BOARD_CASE_SIZE_HEIGHT};
}

inline SDL_Rect getCenteredPosition(int x, int y)
{
    SDL_Rect pos = getPosition(x, y);
    pos.x += BOARD_CASE_SIZE_WIDTH / 2;
    pos.y += BOARD_CASE_SIZE_HEIGHT / 2;
    return pos;
}