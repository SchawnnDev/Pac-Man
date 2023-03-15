#pragma once

#include "constants.h"
#include "utils.h"

#include <SDL_rect.h>
#include <ostream>
#include <cmath>
#include <numbers>

namespace pacman {

    enum class Direction {
        UP = 0,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 1
    };

    class Position {
        int m_x;
        int m_y;

        friend std::ostream &operator<<(std::ostream &, const Position &);

    public:

        constexpr Position() : m_x(0), m_y(0) {}

        constexpr Position(int p_x, int p_y) : m_x(p_x), m_y(p_y) {}

        [[nodiscard]] constexpr int x() const { return m_x; };

        constexpr int &x() { return m_x; };

        [[nodiscard]] constexpr int y() const { return m_y; };

        constexpr int &y() { return m_y; };

        inline bool operator==(const Position &rhs) const noexcept {
            return m_x == rhs.m_x &&
                   m_y == rhs.m_y;
        }

        inline bool operator!=(const Position &rhs) const noexcept {
            return !(rhs == *this);
        }

        [[nodiscard]] constexpr Position add(Position position) const noexcept {
            return {m_x + position.x(), m_y + position.y()};
        }

        [[nodiscard]] constexpr Position subtract(Position position) const noexcept {
            return {m_x - position.x(), m_y - position.y()};
        }

        [[nodiscard]] constexpr Position rotateVec(const Position pivot, int angle) const
        {
            auto angleDegrees = (angle * (std::numbers::pi / 180));
            auto sn = std::sin(angleDegrees);
            auto cn = std::cos(angleDegrees);
            Position result{m_x, m_y};

            // translate point back to origin
            result.x() -= pivot.x();
            result.y() -= pivot.y();

            // rotate point
            auto newX = (int) (result.x() * cn - result.y() * sn);
            auto newY = (int) (result.x() * sn + result.y() * cn);

            // translate point back
            result.x() = newX + pivot.x();
            result.y() = newY + pivot.y();
            return result;
        }

        [[nodiscard]] constexpr Position getPositionAt(Direction p_direction, int count) const noexcept {
            switch (p_direction) {
                case Direction::UP:
                    return {m_x, m_y - count};
                case Direction::DOWN:
                    return {m_x, m_y + count};
                case Direction::LEFT:
                    return {m_x - count, m_y};
                case Direction::RIGHT:
                    return {m_x + count, m_y};
            }

            return {-1, -1};
        }

        constexpr void moveAt(Direction p_direction, int p_pixels) noexcept {
            switch (p_direction) {
                case Direction::UP:
                    m_y -= p_pixels;
                    break;
                case Direction::DOWN:
                    m_y += p_pixels;
                    break;
                case Direction::LEFT:
                    m_x -= p_pixels;
                    break;
                case Direction::RIGHT:
                    m_x += p_pixels;
                    break;
            }
        }

        [[nodiscard]] constexpr int distanceTo(Position p_target) const noexcept {
            auto x = p_target.x() - m_x;
            auto y = p_target.y() - m_y;
            return x * x + y * y;
        }

        constexpr void toPixels() noexcept {
            m_x *= BOARD_CASE_SIZE_WIDTH;
            m_y *= BOARD_CASE_SIZE_HEIGHT;
        }

        constexpr SDL_Rect toSDLRect() noexcept {
            return {m_x, m_y, 0, 0};
        }

    };

    constexpr Position getPosition(int p_x, int p_y) noexcept {
        return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT + BOARD_OFFSET_Y};
    }

    constexpr SDL_Rect getRectPosition(int p_x, int p_y) noexcept {
        return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT + BOARD_OFFSET_Y};
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

    constexpr Direction getOpposite(Direction p_direction) noexcept {
        switch (p_direction) {
            case Direction::UP:
                return Direction::DOWN;
            case Direction::DOWN:
                return Direction::UP;
            case Direction::LEFT:
                return Direction::RIGHT;
            case Direction::RIGHT:
                return Direction::LEFT;
        }
        return Direction::LEFT;
    }

    constexpr Direction getDirectionByAngle(Direction p_direction, int angle) noexcept {
        return Direction(positiveModulo(static_cast<int>(p_direction) - angle / 90, 4));
    }

    constexpr int getDirectionPriority(Direction p_direction) noexcept {
        switch (p_direction) {
            case Direction::UP:
                return 3;
            case Direction::DOWN:
                return 1;
            case Direction::LEFT:
                return 2;
            case Direction::RIGHT:
                return 0;
        }
        return -1;
    }

    inline std::string getDirectionName(Direction p_direction) noexcept {
        switch (p_direction) {
            case Direction::UP:
                return "up";
            case Direction::DOWN:
                return "down";
            case Direction::LEFT:
                return "left";
            case Direction::RIGHT:
                return "right";
        }
        return "";
    }

}
