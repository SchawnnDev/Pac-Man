#include <iostream>
#include "../../include/board/board.h"
#include "../../include/constants.h"
#include "pugixml.hpp"

Board::Board() {

    for (int i = 0; i < BOARD_SIZE_Y; ++i) {
        for (int j = 0; j < BOARD_SIZE_X; ++j) {
            m_grid[i][j] = std::make_shared<BoardCase>(j,i, BoardCaseType::PointPath);
        }
    }

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



