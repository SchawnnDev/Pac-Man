#include <iostream>
#include "../../include/board/board.h"
#include "../../include/constants.h"
#include "pugixml.hpp"
#include "../../include/sprite-handler.h"
#include "../../include/position.h"

Board::Board() {

    for (int i = 0; i < BOARD_SIZE_Y; ++i) {
        for (int j = 0; j < BOARD_SIZE_X; ++j) {
            m_grid[i][j] = std::make_shared<BoardCase>(j,i, BoardCaseType::PointPath);
        }
    }

    m_pointSprite = SpriteHandler::getSprite("point");
    m_bonusSprite = SpriteHandler::getSprite("bonus");
    m_emptyBoardSprite = SpriteHandler::getSprite("board_empty");

}

Board::~Board() {

}

Board::Board(const std::string& p_filePath) : Board() {
    m_filePath = p_filePath;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(p_filePath.c_str());

    if (!result) {
        std::cout << "Could not import board from " << p_filePath.c_str() << ".\n";
        return;
    }

    pugi::xpath_node_set tools_with_timeout = doc.select_nodes(".//case");

    for (pugi::xpath_node node: tools_with_timeout) {
        auto x = node.node().attribute("x").as_int();
        auto y = node.node().attribute("y").as_int();
        auto boardCase = getCase(x, y);
        boardCase->type() = BoardCaseType(node.node().attribute("type").as_int());
    }

    std::cout << "Successfully loaded " << tools_with_timeout.size() << " case(s)!\n";
}

void Board::save(const std::string &p_filePath) {
    std::cout << "Saving board to " << p_filePath.c_str() << ".\n";
    pugi::xml_document doc;
    auto boardNode = doc.append_child("board");

    for (int i = 0; i < m_grid.size(); ++i) {
        for (int j = 0; j < m_grid[i].size(); ++j) {
            auto node = boardNode.append_child("case");
            node.append_attribute("x").set_value(j);
            node.append_attribute("y").set_value(i);
            node.append_attribute("type").set_value(static_cast<int>(m_grid[i][j]->type()));
        }
    }

    doc.save_file(p_filePath.c_str());
    std::cout << "Successfully saved board to " << p_filePath.c_str() << ".\n";
}

bool first = true;

void Board::draw(SDL_Renderer *p_window_renderer, SDL_Texture* p_texture)
{
    SDL_Rect bg = { 0,0, BOARD_SIZE_WIDTH,BOARD_SIZE_HEIGHT };
    SDL_RenderCopy(p_window_renderer,p_texture,&m_emptyBoardSprite->rect(),&bg); // Copie du sprite grâce au SDL_Renderer
    // 10 14
    for (int y = 0; y < BOARD_SIZE_Y; ++y) {
        for (int x = 0; x < BOARD_SIZE_X; ++x) {
            auto caseType = getCase(x, y)->type();
            auto centered = getCenteredPosition(x, y);

/*
            SDL_SetRenderDrawColor(p_window_renderer, 127, 255, 255, 255);
            SDL_Rect rect = {x * BOARD_CASE_SIZE_WIDTH, y * BOARD_CASE_SIZE_HEIGHT, BOARD_CASE_SIZE_WIDTH,
                                BOARD_CASE_SIZE_HEIGHT};
            SDL_RenderDrawRect(p_window_renderer, &rect);
*/

            switch (caseType) {
                case BoardCaseType::PointPath:

                    if(first) std::cout << "(" << x << "," << y << ") -> " << "(" << centered.x << "," << centered.y << ")\n";

                    centered.x -= m_pointSprite->rect().w * 2;
                    centered.y -= m_pointSprite->rect().h * 2;
                    centered.w = m_pointSprite->rect().w * 4;
                    centered.h = m_pointSprite->rect().h * 4;
                    SDL_SetRenderDrawColor(p_window_renderer, 127, 0, 255, 255);
                    SDL_RenderFillRect(p_window_renderer, &centered);
                    // SDL_RenderCopy(p_window_renderer,p_texture,&m_pointSprite->rect(),&centered); // Copie du sprite grâce au SDL_Renderer
                    break;
                case BoardCaseType::BasicPath:
                    break;
                case BoardCaseType::Bonus:
                    centered.x -= m_bonusSprite->rect().w * 2;
                    centered.y -= m_bonusSprite->rect().h * 2;
                    centered.w = m_bonusSprite->rect().w * 4;
                    centered.h = m_bonusSprite->rect().h * 4;
                    SDL_RenderCopy(p_window_renderer,p_texture,&m_bonusSprite->rect(),&centered);
                    break;
                case BoardCaseType::Wall:
                    break;
                case BoardCaseType::GhostHome:
                    break;
                case BoardCaseType::GhostHomeDoorLeft:
                    break;
                case BoardCaseType::GhostHomeDoorRight:
                    break;
                case BoardCaseType::GhostHomeDoor:
                    break;
                case BoardCaseType::Nothing:
                    break;
            }


        }
    }

    if(first) first = false;
}


