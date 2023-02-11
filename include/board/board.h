#pragma once

#include <array>
#include <memory>
#include <SDL.h>
#include "board-case.h"
#include "../constants.h"
#include "../sprite.h"

class Board {
    std::array<std::array<std::shared_ptr<BoardCase>, BOARD_SIZE_X>, BOARD_SIZE_Y> m_grid;
    std::string m_filePath;
    std::shared_ptr<Sprite> m_pointSprite, m_bonusSprite, m_emptyBoardSprite;
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

};
