#pragma once

#include <array>
#include <memory>
#include <SDL.h>
#include <optional>
#include "board-case.h"
#include "../utils/constants.h"
#include "../sprite.h"
#include "../animations/bonus-animation.h"

class Board {
    std::array<std::array<std::shared_ptr<BoardCase>, BOARD_SIZE_X>, BOARD_SIZE_Y> m_grid;
    std::string m_filePath;
    std::shared_ptr<Sprite> m_pointSprite, m_emptyBoardSprite;
    BonusAnimation m_bonusAnimation;
public:
    Board();
    Board(const std::string& p_filePath);

    ~Board();

    [[nodiscard]] const std::array<std::array<std::shared_ptr<BoardCase>, BOARD_SIZE_X>, BOARD_SIZE_Y> &grid() const { return m_grid; };

    std::array<std::array<std::shared_ptr<BoardCase>, BOARD_SIZE_X>, BOARD_SIZE_Y> &grid() { return m_grid; };

    [[nodiscard]] inline const std::shared_ptr<BoardCase>& getCase(int x, int y) const {
        return m_grid[y][x];
    }

    void save(const std::string& p_filePath);

    void draw(SDL_Renderer *p_window_renderer, SDL_Texture* p_texture);

    [[nodiscard]] static inline bool isCase(int p_x, int p_y) {
        return p_x % BOARD_CASE_SIZE_WIDTH == 0 && p_y % BOARD_CASE_SIZE_HEIGHT == 0;
    }

};
