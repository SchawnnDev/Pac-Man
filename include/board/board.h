#pragma once

#include <array>
#include <memory>
#include <SDL.h>
#include <optional>
#include "board-case.h"
#include "../utils/constants.h"
#include "../sprite.h"
#include "../utils/position.h"
#include "../entities/entity.h"

class Board {
    std::array<std::array<BoardCase, BOARD_SIZE_X>, BOARD_SIZE_Y> m_grid;
    std::string m_filePath;
    std::shared_ptr<Sprite> m_pointSprite, m_emptyBoardSprite;
    std::shared_ptr<SpriteAnimation> m_bonusAnimation;
public:
    Board();

    explicit Board(const std::string &p_filePath);

    ~Board();

    [[nodiscard]] const std::array<std::array<BoardCase, BOARD_SIZE_X>, BOARD_SIZE_Y> &
    grid() const { return m_grid; };

    std::array<std::array<BoardCase, BOARD_SIZE_X>, BOARD_SIZE_Y> &grid() { return m_grid; };

    [[nodiscard]] inline const BoardCase &getCase(int x, int y) const {
        return m_grid[y][x];
    }

    void save(const std::string &p_filePath);

    void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture);

    /**
     *
     * @param p_pixelPosition
     * @return
     */
    static inline bool isCase(Position p_pixelPosition) {
        return isCase(p_pixelPosition.x(), p_pixelPosition.y());
    }

    static inline bool isCase(int p_pixelX, int p_pixelY) {
        return p_pixelX % BOARD_CASE_SIZE_WIDTH == 0 &&
               p_pixelY % BOARD_CASE_SIZE_HEIGHT == 0;
    }

    static inline Position findCase(Position p_pixelPosition) {
        return findCase(p_pixelPosition.x(), p_pixelPosition.y());
    }

    static inline Position findCase(int p_pixelX, int p_pixelY) {
        if (p_pixelX < 0 || p_pixelX > BOARD_SIZE_WIDTH || p_pixelY < 0 ||
            p_pixelY > BOARD_SIZE_HEIGHT)
            return {-1, -1};

        return {
                (p_pixelX - (p_pixelX % BOARD_CASE_SIZE_WIDTH)) /
                BOARD_CASE_SIZE_WIDTH,
                (p_pixelY - (p_pixelY % BOARD_CASE_SIZE_HEIGHT)) /
                BOARD_CASE_SIZE_HEIGHT
        };
    }

    static inline bool isCaseCenter(Position p_pixelPosition) {
        return isCaseCenter(p_pixelPosition.x(), p_pixelPosition.y());
    }

    static inline bool isCaseCenter(int p_pixelX, int p_pixelY) {
        Position foundCase = findCase(p_pixelX, p_pixelY);
        if (foundCase.x() == -1 || foundCase.y() == -1) return false;
        auto pos = getCenteredPosition(foundCase.x(), foundCase.y());
        return pos.x() == p_pixelX && pos.y() == p_pixelY;
    }

    [[nodiscard]] bool canEntityMoveTo(const Entity &p_entity, Direction p_direction) const;


};
