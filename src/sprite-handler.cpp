#include <iostream>
#include <memory>
//#include <format>
#include "../include/sprite-handler.h"
#include "pugixml.hpp"

void SpriteHandler::importSprites(const std::string &path) {
    std::cout << "Importing sprite positions: " << path.c_str() << "\n";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());

    if (!result) {
        std::cout << "Could not import sprite.\n";
        return;
    }

    pugi::xpath_node_set tools_with_timeout = doc.select_nodes(".//spr");

    for (pugi::xpath_node node: tools_with_timeout) {
        std::cout << "Loading sprite " << node.node().attribute("name").value() << "...\n";
        auto spr = std::make_shared<Sprite>(node.node().attribute("name").value());
        spr->rect().x = node.node().attribute("x").as_int();
        spr->rect().y = node.node().attribute("y").as_int();
        spr->rect().w = node.node().attribute("w").as_int();
        spr->rect().h = node.node().attribute("h").as_int();
        SpriteHandler::m_sprites.push_back(spr);
    }

    std::cout << "Successfully loaded " << tools_with_timeout.size() << " sprites!\n";

}

std::shared_ptr<Sprite> SpriteHandler::getSprite(const std::string &name) {
    for (auto sprite: SpriteHandler::m_sprites) {
        if (sprite->name() == name)
            return sprite;
    }
    return nullptr;
}

SpriteHandler::~SpriteHandler() {
    //std::destroy(m_sprites.begin(), m_sprites.end());
}

SpriteHandler::SpriteHandler() {
    //m_sprites = {};
}
