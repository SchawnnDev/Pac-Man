#include <iostream>
#include <memory>
#include "sprite-handler.h"
#include "pugixml.hpp"
#include "entities/pacman.h"
#include "animations/pacman/pacman-down-animation.h"
#include "animations/pacman/pacman-dying-animation.h"
#include "animations/pacman/pacman-up-animation.h"
#include "animations/pacman/pacman-left-animation.h"
#include "animations/pacman/pacman-right-animation.h"
#include "animations/bonus-animation.h"

void SpriteHandler::importSprites(const std::string &path)
{
    std::cout << "Importing sprite positions: " << path.c_str() << "\n";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());

    if (!result)
    {
        std::cout << "Could not import sprite.\n";
        return;
    }

    pugi::xpath_node_set tools_with_timeout = doc.select_nodes(".//spr");

    for (pugi::xpath_node node: tools_with_timeout)
    {
        std::cout << "Loading sprite " << node.node().attribute("name").value()
                  << "...\n";
        Sprite spr{node.node().attribute("name").value()};
        spr.rect().x = node.node().attribute("x").as_int();
        spr.rect().y = node.node().attribute("y").as_int();
        spr.rect().w = node.node().attribute("w").as_int();
        spr.rect().h = node.node().attribute("h").as_int();
        SpriteHandler::m_sprites.push_back(spr);
    }

    std::cout << "Successfully loaded " << tools_with_timeout.size()
              << " sprites!\n";

}

std::optional<Sprite> SpriteHandler::getSprite(const std::string &name)
{
    for (auto sprite: SpriteHandler::m_sprites)
    {
        if (sprite.name() == name)
            return sprite;
    }
    return std::nullopt;
}

void SpriteHandler::initAnimations()
{
    m_spriteAnimations["pacman-down"] = std::make_shared<PacmanDownAnimation>();
    m_spriteAnimations["pacman-up"] = std::make_shared<PacmanUpAnimation>();
    m_spriteAnimations["pacman-left"] = std::make_shared<PacmanLeftAnimation>();
    m_spriteAnimations["pacman-right"] = std::make_shared<PacmanRightAnimation>();
    m_spriteAnimations["pacman-dying"] = std::make_shared<PacmanDyingAnimation>();
    m_spriteAnimations["bonus"] = std::make_shared<BonusAnimation>();
}

SpriteHandler::~SpriteHandler()
{
    //std::destroy(m_sprites.begin(), m_sprites.end());
}

SpriteHandler::SpriteHandler()
{
    //m_sprites = {};
}

std::shared_ptr<SpriteAnimation>
SpriteHandler::getSpriteAnimation(const std::string &name)
{
    return !m_spriteAnimations.contains(name) ? nullptr
                                              : m_spriteAnimations[name];
}
