#pragma once

#include <string_view>
#include <array>
#include <memory>
#include <optional>
#include <iostream>

#include <SDL.h>

#include "board-case.h"
#include "sprites/sprite.h"
#include "sprites/sprite-resources-structs.h"
#include "utils/constants.h"
#include "utils/position.h"
#include "screens/drawable.h"
#include "game/player.h"

namespace pacman {

    class Board : public Drawable {
        std::array<BoardCase, BOARD_SIZE_X * BOARD_SIZE_Y> m_grid;
        std::string m_filePath;
        BoardResources m_boardResources;
        std::optional<SpriteAnimation> m_currentAnimation;

        PlayerPtr& m_currentPlayer;

        size_t m_leftDoorIndex;
        size_t m_rightDoorIndex;
        size_t m_homeDoorIndex;
    public:

        Board(const std::optional<std::string> &p_filePath, PlayerPtr& p_currentPlayer, BoardResources p_boardResources) noexcept;

        ~Board() = default;

        /**
         * @return BoardCase grid, covering the whole board
         */
        [[nodiscard]] std::array<BoardCase, BOARD_SIZE_X * BOARD_SIZE_Y> const &grid() const noexcept { return m_grid; };

        /**
         * @return BoardCase grid, covering the whole board
         */
        std::array<BoardCase, BOARD_SIZE_X * BOARD_SIZE_Y> &grid() noexcept { return m_grid; };

        /**
         * @return Index in grid of left door
         */
        [[nodiscard]] size_t leftDoorIndex() const { return m_leftDoorIndex; }

        /**
         * @return Index in grid of right door
         */
        [[nodiscard]] size_t rightDoorIndex() const { return m_rightDoorIndex; }

        /**
         * @return Index in grid of home door
         */
        [[nodiscard]] size_t homeDoorIndex() const { return m_homeDoorIndex; }

        /**
         * @return Current sprite animation of drawable
         */
        [[nodiscard]] auto const &currentAnimation() const { return m_currentAnimation; }

        /**
         * @return Reference to the current sprite animation of drawable
         */
        auto &currentAnimation() { return m_currentAnimation; }

        /**
         * @param p_position Position index
         * @return Check if indexes p_position are valid indexes
         */
        static constexpr bool checkGridCoordinates(Position p_position) noexcept {
            return checkGridCoordinates(p_position.x(), p_position.y());
        }

        /**
         * @param p_x X index
         * @param p_y Y index
         * @return Check if indexes p_x, p_y are valid indexes
         */
        static constexpr bool checkGridCoordinates(int p_x, int p_y) noexcept {
            return p_x < 0 || p_y < 0 || getGridIndex(p_x, p_y) < BOARD_SIZE_X * BOARD_SIZE_Y;
        }

        /**
         * @param p_x X index
         * @param p_y Y index
         * @return Calculated grid index from (p_x, p_y)
         */
        static constexpr size_t getGridIndex(int p_x, int p_y) noexcept {
            return BOARD_SIZE_X * p_y + p_x;
        }

        /**
         * @param p_position Position to get the grid index from
         * @return Calculated grid index from position
         */
        static constexpr size_t getGridIndex(Position p_position) noexcept {
            return getGridIndex(p_position.x(), p_position.y());
        }

        /**
         * @param p_position x,y position index
         * @return Get boardcase from grid at position
         */
        [[nodiscard]] inline BoardCase const &getCase(Position p_position) const noexcept {
            return getCase(p_position.x(), p_position.y());
        }

        /**
         * @param p_position x,y position index
         * @return Get boardcase from grid at position
         */
        [[nodiscard]] inline BoardCase &getCase(Position p_position) noexcept {
            return getCase(p_position.x(), p_position.y());
        }

        /**
         * @param p_x X index
         * @param p_y Y index
         * @return Get boardcase from grid at (p_x, p_y)
         */
        [[nodiscard]] inline BoardCase const &getCase(int p_x, int p_y) const noexcept {
            return m_grid[getGridIndex(p_x, p_y)];
        }

        /**
         * @param p_x X index
         * @param p_y Y index
         * @return Get boardcase from grid at (p_x, p_y)
         */
        inline BoardCase &getCase(int p_x, int p_y) noexcept {
            return m_grid[getGridIndex(p_x, p_y)];
        }

        /**
         * @param p_position Position to check if is on boardcase
         * @param p_boardCaseIndex Index of the case in grid
         * @return Found case position is equals to given boardCaseIndex
         */
        [[nodiscard]] static constexpr bool isOnBoardCase(Position p_position, size_t p_boardCaseIndex) noexcept {
            auto caseFound = Board::findCase(p_position);
            if (caseFound.x() == -1 || caseFound.y() == -1) return false;
            return getGridIndex(caseFound.x(), caseFound.y()) == p_boardCaseIndex;
        }

        /**
         * @param p_position Position
         * @return Checks if position is left door position
         */
        [[nodiscard]] constexpr bool isOnLeftDoor(Position p_position) const noexcept {
            return isOnBoardCase(p_position, m_leftDoorIndex);
        }

        /**
         * @param p_position Position
         * @return Checks if position is right door position
         */
        [[nodiscard]] constexpr bool isOnRightDoor(Position p_position) const noexcept {
            return isOnBoardCase(p_position, m_rightDoorIndex);
        }

        /**
         * @param p_position Square position
         * @param p_direction Direcetion of the square to get to
         * @return Get the boardcase at a position and given direction to find the next square
         */
        [[nodiscard]] std::optional<BoardCase> getBoardCaseAtPixels(Position p_position, Direction p_direction) noexcept;

        /**
         * @param p_position Index of grid (x, y)
         * @return Get case in grid at given index (x, y)
         */
        [[nodiscard]] BoardCase& getBoardCaseAtPixels(Position p_position);

        /**
         * @param p_filePath Save board to file
         */
        void save(const std::string &p_filePath) const noexcept;

        /**
         * Reset board
         */
        void reset() noexcept;


        /**
         * Draw board to screen
         * @param p_window_renderer Window renderer
         * @param p_texture Texture to get sprite from
         */
        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

        /**
         * @param p_pixelPosition Position
         * @return Given position is a case or not
         */
        static constexpr bool isCase(Position p_pixelPosition) noexcept {
            return isCase(p_pixelPosition.x(), p_pixelPosition.y());
        }

        /**
         * @param p_pixelX Position x
         * @param p_pixelY Position y
         * @return Given position is a case or not
         */
        static constexpr bool isCase(int p_pixelX, int p_pixelY) noexcept {
            return p_pixelX % BOARD_CASE_SIZE_WIDTH == 0 &&
                   (p_pixelY - BOARD_OFFSET_Y) % BOARD_CASE_SIZE_HEIGHT == 0;
        }

        /**
         * @param p_pixelPosition Position
         * @return Find case index in grid of pixel position
         */
        static constexpr Position findCase(Position p_pixelPosition) noexcept {
            return findCase(p_pixelPosition.x(), p_pixelPosition.y());
        }

        /**
         * @param p_pixelX Pixel position X
         * @param p_pixelY Pixel position Y
         * @return Find case index in grid of pixel x and y
         */
        static constexpr Position findCase(int p_pixelX, int p_pixelY) noexcept {
            p_pixelY -= BOARD_OFFSET_Y;

            if (p_pixelX < 0 || p_pixelX > BOARD_SIZE_WIDTH || p_pixelY < 0 ||
                p_pixelY > BOARD_SIZE_HEIGHT)
                return {-1, -1};

            return {
                    (p_pixelX - (p_pixelX % BOARD_CASE_SIZE_WIDTH)) / BOARD_CASE_SIZE_WIDTH,
                    (p_pixelY - (p_pixelY % BOARD_CASE_SIZE_HEIGHT)) / BOARD_CASE_SIZE_HEIGHT
            };
        }

        /**
         * @param p_pixelPosition Position to check
         * @return Checks if position is a case and if position is in the center of a case
         */
        static constexpr bool isCaseCenter(Position p_pixelPosition) noexcept {
            return isCaseCenter(p_pixelPosition.x(), p_pixelPosition.y());
        }

        /**
         * @param p_pixelX Pixel position x
         * @param p_pixelY Pixel position y
         * @return Checks if (x, y) is a case and if (x, y) is in the center of a case
         */
        static constexpr bool isCaseCenter(int p_pixelX, int p_pixelY) noexcept {
            Position foundCase = findCase(p_pixelX, p_pixelY);
            if (foundCase.x() == -1 || foundCase.y() == -1) return false;
            auto pos = getCenteredPosition(foundCase.x(), foundCase.y());
            return pos.x() == p_pixelX && pos.y() == p_pixelY;
        }

        /**
         * Load board from current player
         */
        void load();

        /**
         * Starts level end animation
         * (board flashing white and normal)
         */
        void startLevelEndAnimation();
    };

}