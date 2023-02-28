#include <iostream>
#include <utility>

#include "pugixml.hpp"

#include "board/board.h"
#include "sprite-handler.h"

Board::Board(const std::optional<std::string> &p_filePath, BoardResources p_boardResources) noexcept
        : m_filePath{p_filePath.value_or(std::string{})}, m_boardResources{std::move(p_boardResources)},
          m_leftDoorIndex{-1}, m_rightDoorIndex{-1} {
    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
            m_grid[getGridIndex(x, y)] = {x, y, BoardCaseType::PointPath, std::nullopt};

    if (!p_filePath)
        return;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_filePath.c_str());

    if (!result) {
        std::cout << "Could not import board from " << m_filePath
                  << std::endl;
        return;
    }

    pugi::xpath_node_set tools_with_timeout = doc.select_nodes(".//case");

    for (pugi::xpath_node node: tools_with_timeout) {
        auto x = node.node().attribute("x").as_int();
        auto y = node.node().attribute("y").as_int();
        auto &boardCase = getCase(x, y);
        boardCase.type() = BoardCaseType(node.node().attribute("type").as_int());

        switch (boardCase.type()) {
            case BoardCaseType::Bonus:
                boardCase.animation() = m_boardResources.bonusAnimation;
                break;
            case BoardCaseType::DoorLeft:
                m_leftDoorIndex = getGridIndex(x, y);
                break;
            case BoardCaseType::DoorRight:
                m_rightDoorIndex = getGridIndex(x, y);
                break;
            default:
                break;
        }


    }

    std::cout << "Successfully loaded " << tools_with_timeout.size()
              << " case(s)!" << std::endl;
}

void Board::save(const std::string &p_filePath) const noexcept {
    std::cout << "Saving board to " << p_filePath.c_str() << "." << std::endl;
    pugi::xml_document doc;
    auto boardNode = doc.append_child("board");

    for (int i = 0; i < BOARD_SIZE_X; ++i) {
        for (int j = 0; j < BOARD_SIZE_Y; ++j) {
            auto node = boardNode.append_child("case");
            node.append_attribute("x").set_value(j);
            node.append_attribute("y").set_value(i);
            node.append_attribute("type").set_value(
                    static_cast<int>(getCase(i, j).type()));
        }
    }

    doc.save_file(p_filePath.c_str());
    std::cout << "Successfully saved board to " << p_filePath.c_str() << "." << std::endl;
}

bool first = true;

void Board::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept {
    SDL_Rect bg = {0, 0, BOARD_SIZE_WIDTH, BOARD_SIZE_HEIGHT};
    //std::cout << m_boardResources.emptyBoardSprite.name() << std::endl;
    SDL_RenderCopy(p_window_renderer, p_texture, &m_boardResources.emptyBoardSprite.rect(),
                   &bg); // Copie du sprite grâce au SDL_Renderer

    // 10 14
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            auto &_case = getCase(x, y);
            auto caseType = _case.type();
            auto centered = getRectCenteredPosition(x, y);

/*            SDL_SetRenderDrawColor(p_window_renderer, 255, 255, 255, 255);
            SDL_Rect sdlRect = {x * BOARD_CASE_SIZE_WIDTH, y * BOARD_CASE_SIZE_HEIGHT, BOARD_CASE_SIZE_WIDTH,
                                BOARD_CASE_SIZE_HEIGHT};
            SDL_RenderDrawRect(p_window_renderer, &sdlRect);
            SDL_SetRenderDrawColor(p_window_renderer, 255, 255, 255, 255);*/

            switch (caseType) {
                case BoardCaseType::PointPath: {
                    //  if (first)
                    //    std::cout << "(" << x << "," << y << ") -> " << "("
                    //             << centered.x << "," << centered.y << ")\n";
                    auto pointSprite = m_boardResources.pointSprite;
                    centered.x -= pointSprite.rect().w * 2;
                    centered.y -= pointSprite.rect().h * 2;
                    centered.w = pointSprite.rect().w * 4;
                    centered.h = pointSprite.rect().h * 4;
                    //   SDL_SetRenderDrawColor(p_window_renderer, 127, 0, 255, 255);
                    // SDL_RenderFillRect(p_window_renderer, &centered);
                    SDL_RenderCopy(p_window_renderer, p_texture,
                                   &pointSprite.rect(),
                                   &centered); // Copie du sprite grâce au SDL_Renderer
                    break;
                }
                case BoardCaseType::Bonus: {
                    if (!_case.animation().has_value()) break;
                    auto &spriteAnimation = _case.animation().value();
                    auto found = spriteAnimation.display();
                    if (!found) break;
                    auto sprite = found.value();
                    centered.x -= sprite.rect().w * 2;
                    centered.y -= sprite.rect().h * 2;
                    centered.w = sprite.rect().w * 4;
                    centered.h = sprite.rect().h * 4;
                    SDL_RenderCopy(p_window_renderer, p_texture,
                                   &sprite.rect(), &centered);
                    break;
                }
                case BoardCaseType::BasicPath:
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
                case BoardCaseType::DoorLeft:
                    break;
                case BoardCaseType::DoorRight:
                    break;
            }

        }
    }

    if (first) first = false;
}
