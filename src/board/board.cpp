#include <iostream>
#include <utility>

#include "pugixml.hpp"

#include "board/board.h"
#include "sprites/sprite-handler.h"

using namespace pacman;

Board::Board(const std::optional<std::string> &p_filePath, BoardResources p_boardResources) noexcept
        : m_filePath{p_filePath.value_or(std::string{})}
        , m_boardResources{std::move(p_boardResources)}
        , m_leftDoorIndex{0}
        , m_rightDoorIndex{0}
        , m_homeDoorIndex{0}
        {
    for (int x = 0; x < BOARD_SIZE_X; ++x)
        for (int y = 0; y < BOARD_SIZE_Y; ++y)
            m_grid[getGridIndex(x, y)] = {x, y, BoardCaseType::PointPath, 0, std::nullopt};

    if (!p_filePath)
        return;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_filePath.c_str());

    if (!result) {
        std::cout << "Could not import board from " << m_filePath
                  << std::endl;
        return;
    }

    auto tools_with_timeout = doc.select_nodes(".//case");

    for (pugi::xpath_node node: tools_with_timeout) {
        auto x = node.node().attribute("x").as_int();
        auto y = node.node().attribute("y").as_int();
        auto &boardCase = getCase(x, y);
        boardCase.type() = BoardCaseType(node.node().attribute("type").as_int());
        boardCase.flags() = node.node().attribute("flags").as_int(0);

        switch (boardCase.type()) {
            case BoardCaseType::Bonus:
                boardCase.animation() = m_boardResources.bonusAnimation;
                break;
            case BoardCaseType::PointPath:
                boardCase.animation() = SpriteAnimation{{m_boardResources.pointSprite}};
                boardCase.animation()->singleSprite() = true;
                break;
            case BoardCaseType::DoorLeft:
                m_leftDoorIndex = getGridIndex(x, y);
                break;
            case BoardCaseType::DoorRight:
                m_rightDoorIndex = getGridIndex(x, y);
                break;
            case BoardCaseType::GhostHomeDoor:
                m_homeDoorIndex = getGridIndex(x, y);
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
    if(!activated()) return;

    SDL_Rect bg = {0, BOARD_OFFSET_Y, BOARD_SIZE_WIDTH, BOARD_SIZE_HEIGHT};
    SDL_RenderCopy(p_window_renderer, p_texture, &m_boardResources.emptyBoardSprite.rect(),
                   &bg); // Copie du sprite grâce au SDL_Renderer

    // 10 14
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            getCase(x, y).draw(p_window_renderer, p_texture);
        }
    }

    if (first) first = false;
}

std::optional<BoardCase> Board::getBoardCaseAtPixels(Position p_position, Direction p_direction) noexcept {
    auto caseFound = Board::findCase(p_position);
    if (caseFound.x() == -1 || caseFound.y() == -1) return std::nullopt;
    auto nextCasePos = caseFound.getPositionAt(p_direction, 1);
    if (!Board::checkGridCoordinates(nextCasePos)) return std::nullopt;
    return getCase(nextCasePos);
}

BoardCase& Board::getBoardCaseAtPixels(Position p_position) {
    auto caseFound = Board::findCase(p_position);
    if (caseFound.x() == -1 || caseFound.y() == -1) throw;
    return getCase(caseFound);
}
