#pragma once

#include "constants.h"
#include <SDL_rect.h>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Position
{
    int m_x;
    int m_y;
public:

    Position() : m_x(0), m_y(0)
    {}

    ~Position();

    Position(int p_x, int p_y) : m_x(p_x), m_y(p_y)
    {}

    [[nodiscard]] const int &x() const
    { return m_x; };

    int &x()
    { return m_x; };

    [[nodiscard]] const int &y() const
    { return m_y; };

    int &y()
    { return m_y; };


    inline bool operator==(const Position &rhs) const
    {
        return m_x == rhs.m_x &&
               m_y == rhs.m_y;
    }

    inline bool operator!=(const Position &rhs) const
    {
        return !(rhs == *this);
    }

};


inline Position getPosition(int p_x, int p_y)
{
    return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT};
}

inline SDL_Rect getRectPosition(int p_x, int p_y)
{
    return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT};
}

inline Position getCenteredPosition(int p_x, int p_y)
{
    Position pos = getPosition(p_x, p_y);
    pos.x() += BOARD_CASE_SIZE_WIDTH / 2;
    pos.y() += BOARD_CASE_SIZE_HEIGHT / 2;
    return pos;
}

inline SDL_Rect getRectCenteredPosition(int p_x, int p_y)
{
    auto pos = getCenteredPosition(p_x, p_y);
    return {pos.x(), pos.y()};
}

inline SDL_Rect
calculateSprite(SDL_Rect p_center, SDL_Rect p_sprite, int p_zoomFactor)
{
    p_center.x -= p_sprite.w * (p_zoomFactor / 2);
    p_center.y -= p_sprite.h * (p_zoomFactor / 2);
    p_center.w = p_sprite.w * p_zoomFactor;
    p_center.h = p_sprite.h * p_zoomFactor;
    return p_center;
}