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

    constexpr Position() : m_x(0), m_y(0) {}

    constexpr Position(int p_x, int p_y) : m_x(p_x), m_y(p_y) {}

    [[nodiscard]] constexpr int const &x() const { return m_x; };

    constexpr int &x() { return m_x; };

    [[nodiscard]] constexpr int const &y() const { return m_y; };

    constexpr int &y() { return m_y; };

    inline bool operator==(const Position &rhs) const noexcept {
        return m_x == rhs.m_x &&
               m_y == rhs.m_y;
    }

    inline bool operator!=(const Position &rhs) const noexcept {
        return !(rhs == *this);
    }

    [[nodiscard]] constexpr Position getPositionAt(Direction p_direction) const noexcept {
        switch (p_direction) {
            case Direction::UP:
                return {m_x, m_y + 1};
            case Direction::DOWN:
                return {m_x, m_y - 1};
            case Direction::LEFT:
                return {m_x - 1, m_y};
            case Direction::RIGHT:
                return {m_x + 1, m_y};
        }

        return {-1, -1};
    }

};


constexpr Position getPosition(int p_x, int p_y) noexcept {
    return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT};
}

constexpr SDL_Rect getRectPosition(int p_x, int p_y) noexcept {
    return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT};
}

constexpr Position getCenteredPosition(int p_x, int p_y) noexcept {
    Position pos = getPosition(p_x, p_y);
    pos.x() += BOARD_CASE_SIZE_WIDTH / 2;
    pos.y() += BOARD_CASE_SIZE_HEIGHT / 2;
    return pos;
}

constexpr SDL_Rect getRectCenteredPosition(int p_x, int p_y) noexcept {
    auto pos = getCenteredPosition(p_x, p_y);
    return {pos.x(), pos.y()};
}

constexpr SDL_Rect
calculateSprite(SDL_Rect p_center, SDL_Rect p_sprite, int p_zoomFactor) noexcept {
    p_center.x -= p_sprite.w * (p_zoomFactor / 2);
    p_center.y -= p_sprite.h * (p_zoomFactor / 2);
    p_center.w = p_sprite.w * p_zoomFactor;
    p_center.h = p_sprite.h * p_zoomFactor;
    return p_center;
}