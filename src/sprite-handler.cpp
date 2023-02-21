#include <iostream>
#include <memory>

#include "pugixml.hpp"

#include "sprite-handler.h"
#include "animations/pacman/pacman-down-animation.h"
#include "animations/pacman/pacman-dying-animation.h"
#include "animations/pacman/pacman-up-animation.h"
#include "animations/pacman/pacman-left-animation.h"
#include "animations/pacman/pacman-right-animation.h"
#include "animations/bonus-animation.h"

void SpriteHandler::importSprites(std::string_view path) noexcept
{
    std::cout << "Importing sprite positions: " << path << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(std::string{path}.c_str());

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

std::optional<Sprite> SpriteHandler::getSprite(std::string_view name) const noexcept
{
    for (auto sprite: SpriteHandler::m_sprites)
    {
        if (sprite.name() == name)
            return sprite;
    }
    return std::nullopt;
}

void SpriteHandler::initAnimations() noexcept
{
    m_spriteAnimations["pacman-down"] = std::make_shared<PacmanDownAnimation>(std::vector<Sprite>{});
    m_spriteAnimations["pacman-up"] = std::make_shared<PacmanUpAnimation>(std::vector<Sprite>{});
    m_spriteAnimations["pacman-left"] = std::make_shared<PacmanLeftAnimation>(std::vector<Sprite>{});
    m_spriteAnimations["pacman-right"] = std::make_shared<PacmanRightAnimation>(std::vector<Sprite>{});
    m_spriteAnimations["pacman-dying"] = std::make_shared<PacmanDyingAnimation>(
            getSprites("pacman_dying_1", "pacman_dying_2", "pacman_dying_3",
                        "pacman_dying_4", "pacman_dying_5", "pacman_dying_6",
                        "pacman_dying_7", "pacman_dying_8", "pacman_dying_9",
                        "pacman_dying_10"));
    m_spriteAnimations["bonus"] = std::make_shared<BonusAnimation>(std::vector<Sprite>{});
}

std::optional<SpriteAnimationPtr>
SpriteHandler::getSpriteAnimation(std::string_view name) noexcept
{
    if (auto it = m_spriteAnimations.find(std::string{name}); it != std::end(m_spriteAnimations))
        return std::make_optional(it->second);
    else
        return std::nullopt;
}

SpriteHandler::SpriteHandler(std::string_view path) noexcept
{
    importSprites(path);
    initAnimations();
    initStructs();
}

void SpriteHandler::initStructs() noexcept
{
    m_pacmanAnimations = {
            m_spriteAnimations["pacman-up"],
            m_spriteAnimations["pacman-down"],
            m_spriteAnimations["pacman-left"],
            m_spriteAnimations["pacman-right"],
            m_spriteAnimations["pacman-dying"],
    };
}