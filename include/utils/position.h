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

        /**
         * @param position Position to add
         * @return Added position
         */
        [[nodiscard]] constexpr Position add(Position position) const noexcept {
            return {m_x + position.x(), m_y + position.y()};
        }

        /**
         * @param position Position to subtract
         * @return Subtracted position
         */
        [[nodiscard]] constexpr Position subtract(Position position) const noexcept {
            return {m_x - position.x(), m_y - position.y()};
        }

        /**
         * @param pivot Point to rotate from
         * @param angle Angle to rotate from
         * @return This position rotated from angle degrees from pivot position
         */
        [[nodiscard]] Position rotateVec(const Position pivot, int angle) const
        {
            auto angleDegrees = (angle * (std::numbers::pi / 180));
            auto const sn = std::sin(angleDegrees);
            auto const cn = std::cos(angleDegrees);
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

        /**
         * @param p_direction Move direction
         * @param count Pixels to move to
         * @return Position calculated from direction and count to move
         */
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

        /**
         * @param p_direction Direction to move to
         * @param p_pixels Number of pixels to move to
         */
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

        /**
         * @param p_target Target
         * @return Calculated distance between this position and target
         */
        [[nodiscard]] constexpr int distanceTo(Position p_target) const noexcept {
            auto x = p_target.x() - m_x;
            auto y = p_target.y() - m_y;
            return x * x + y * y;
        }

        /**
         * @return Grid position to pixels
         */
        constexpr void toPixels() noexcept {
            m_x *= BOARD_CASE_SIZE_WIDTH;
            m_y *= BOARD_CASE_SIZE_HEIGHT;
        }

        /**
         * @return SDL_Rect form position with width and height = 0
         */
        constexpr SDL_Rect toSDLRect() noexcept {
            return {m_x, m_y, 0, 0};
        }

    };

    /**
     * @param p_x x position (grid position)
     * @param p_y y position (grid position)
     * @return Calculates pixel position of x & y
     */
    constexpr Position getPosition(int p_x, int p_y) noexcept {
        return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT + BOARD_OFFSET_Y};
    }

    /**
     * @param p_x x position (grid position)
     * @param p_y y position (grid position)
     * @return Calculates pixel position of x & y (sdl rect)
     */
    constexpr SDL_Rect getRectPosition(int p_x, int p_y) noexcept {
        return {p_x * BOARD_CASE_SIZE_WIDTH, p_y * BOARD_CASE_SIZE_HEIGHT + BOARD_OFFSET_Y};
    }

    /**
     * @param p_x x position
     * @param p_y y position
     * @return Calculates center position of x & y
     */
    constexpr Position getCenteredPosition(int p_x, int p_y) noexcept {
        Position pos = getPosition(p_x, p_y);
        pos.x() += BOARD_CASE_SIZE_WIDTH / 2;
        pos.y() += BOARD_CASE_SIZE_HEIGHT / 2;
        return pos;
    }

    /**
     * @param p_x x position
     * @param p_y y position
     * @return Calculates center position of x & y (sdl rect)
     */
    constexpr SDL_Rect getRectCenteredPosition(int p_x, int p_y) noexcept {
        auto pos = getCenteredPosition(p_x, p_y);
        return {pos.x(), pos.y()};
    }

    /**
     *
     * @param p_direction direction to get opposite from
     * @return opposite direction
     */
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

    /**
     *
     * @param p_direction start direction to calculate angle from
     * @param angle angle
     * @return direction get from start direction + angle
     */
    constexpr Direction getDirectionByAngle(Direction p_direction, int angle) noexcept {
        return Direction(positiveModulo(static_cast<int>(p_direction) - angle / 90, 4));
    }

    /**
     *
     * @param p_direction direction to get priority from
     * @return priority of given direction
     */
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

    /**
     * @param p_direction direction to get the name from
     * @return name of given direction
     */
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
