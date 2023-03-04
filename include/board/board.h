#pragma once

#include <string_view>
#include <array>
#include <memory>
#include <optional>
#include <iostream>

#include <SDL.h>

#include "board-case.h"
#include "sprite.h"
#include "sprite-animation-structs.h"
#include "utils/constants.h"
#include "utils/position.h"

namespace pacman {

    class Board {
        std::array<BoardCase, BOARD_SIZE_X * BOARD_SIZE_Y> m_grid;
        std::string m_filePath;
        BoardResources m_boardResources;

        size_t m_leftDoorIndex;
        size_t m_rightDoorIndex;
    public:

        Board(const std::optional<std::string> &p_filePath, BoardResources p_boardResources) noexcept;

        ~Board() = default;

        [[nodiscard]] std::array<BoardCase, BOARD_SIZE_X * BOARD_SIZE_Y> const &
        grid() const noexcept { return m_grid; };

        std::array<BoardCase, BOARD_SIZE_X * BOARD_SIZE_Y> &grid() noexcept { return m_grid; };

        [[nodiscard]] size_t leftDoorIndex() const { return m_leftDoorIndex; }

        [[nodiscard]] size_t rightDoorIndex() const { return m_rightDoorIndex; }

        static constexpr bool checkGridCoordinates(Position p_position) noexcept {
            return checkGridCoordinates(p_position.x(), p_position.y());
        }

        static constexpr bool checkGridCoordinates(int p_x, int p_y) noexcept {
            return p_x < 0 || p_y < 0 || getGridIndex(p_x, p_y) < BOARD_SIZE_X * BOARD_SIZE_Y;
        }

        static constexpr size_t getGridIndex(int p_x, int p_y) noexcept {
            return BOARD_SIZE_X * p_y + p_x;
        }

        [[nodiscard]] inline BoardCase const &getCase(Position p_position) const noexcept {
            return getCase(p_position.x(), p_position.y());
        }

        [[nodiscard]] inline BoardCase const &getCase(int p_x, int p_y) const noexcept {
            return m_grid[getGridIndex(p_x, p_y)];
        }

        inline BoardCase &getCase(int p_x, int p_y) noexcept {
            return m_grid[getGridIndex(p_x, p_y)];
        }

        [[nodiscard]] static constexpr bool isOnBoardCase(Position p_position, size_t p_boardCaseIndex) noexcept {
            auto caseFound = Board::findCase(p_position);
            if (caseFound.x() == -1 || caseFound.y() == -1) return false;
            return getGridIndex(caseFound.x(), caseFound.y()) == p_boardCaseIndex;
        }

        [[nodiscard]] constexpr bool isOnLeftDoor(Position p_position) const noexcept {
            return isOnBoardCase(p_position, m_leftDoorIndex);
        }

        [[nodiscard]] constexpr bool isOnRightDoor(Position p_position) const noexcept {
            return isOnBoardCase(p_position, m_rightDoorIndex);
        }

        [[nodiscard]] std::optional<BoardCase>
        getBoardCaseAtPixels(Position p_position, Direction p_direction) const noexcept;

        [[nodiscard]] std::optional<BoardCase> getBoardCaseAtPixels(Position p_position) const noexcept;

        void save(const std::string &p_filePath) const noexcept;

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept;

        /**
         *
         * @param p_pixelPosition
         * @return
         */
        static constexpr bool isCase(Position p_pixelPosition) noexcept {
            return isCase(p_pixelPosition.x(), p_pixelPosition.y());
        }

        static constexpr bool isCase(int p_pixelX, int p_pixelY) noexcept {
            return p_pixelX % BOARD_CASE_SIZE_WIDTH == 0 &&
                   p_pixelY % BOARD_CASE_SIZE_HEIGHT == 0;
        }

        static constexpr Position findCase(Position p_pixelPosition) noexcept {
            return findCase(p_pixelPosition.x(), p_pixelPosition.y());
        }

        static constexpr Position findCase(int p_pixelX, int p_pixelY) noexcept {
            if (p_pixelX < 0 || p_pixelX > BOARD_SIZE_WIDTH || p_pixelY < 0 ||
                p_pixelY > BOARD_SIZE_HEIGHT)
                return {-1, -1};

            return {
                    (p_pixelX - (p_pixelX % BOARD_CASE_SIZE_WIDTH)) / BOARD_CASE_SIZE_WIDTH,
                    (p_pixelY - (p_pixelY % BOARD_CASE_SIZE_HEIGHT)) / BOARD_CASE_SIZE_HEIGHT
            };
        }

        static constexpr bool isCaseCenter(Position p_pixelPosition) noexcept {
            return isCaseCenter(p_pixelPosition.x(), p_pixelPosition.y());
        }

        static constexpr bool isCaseCenter(int p_pixelX, int p_pixelY) noexcept {
            Position foundCase = findCase(p_pixelX, p_pixelY);
            if (foundCase.x() == -1 || foundCase.y() == -1) return false;
            auto pos = getCenteredPosition(foundCase.x(), foundCase.y());
            return pos.x() == p_pixelX && pos.y() == p_pixelY;
        }

    };

}