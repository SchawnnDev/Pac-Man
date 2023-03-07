#include <iostream>

#include "pugixml.hpp"

#include "sprite-handler.h"

using namespace pacman;

void SpriteHandler::importSprites(std::string_view path) noexcept
{
    std::cout << "Importing sprite positions: " << path << std::endl;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(std::string{path}.c_str());

    if (!result)
    {
        std::cout << "Could not import sprite." << std::endl;;
        return;
    }

    pugi::xpath_node_set tools_with_timeout = doc.select_nodes(".//spr");

    for (pugi::xpath_node node: tools_with_timeout)
    {
        std::cout << "Loading sprite " << node.node().attribute("name").value()
                  << "..." << std::endl;
        Sprite spr{node.node().attribute("name").value()};
        spr.rect().x = node.node().attribute("x").as_int();
        spr.rect().y = node.node().attribute("y").as_int();
        spr.rect().w = node.node().attribute("w").as_int();
        spr.rect().h = node.node().attribute("h").as_int();
        SpriteHandler::m_sprites.push_back(spr);
    }

    std::cout << "Successfully loaded " << tools_with_timeout.size()
              << " sprites!" << std::endl;

}

std::optional<Sprite>
SpriteHandler::getSprite(std::string_view name) const noexcept
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
    std::cout << "Initializing sprite animations..." << std::endl;

    // Pacman
    m_spriteAnimations["pacman-down"] = SpriteAnimation{
            getSprites("full_pacman", "pacman_down_little_open", "pacman_down_big_open"),
            false, 2};
    m_spriteAnimations["pacman-up"] = SpriteAnimation{
            getSprites("full_pacman", "pacman_up_little_open", "pacman_up_big_open"), false,
            2};
    m_spriteAnimations["pacman-left"] = SpriteAnimation{
            getSprites("full_pacman", "pacman_left_little_open", "pacman_left_big_open"),
            false, 2};
    m_spriteAnimations["pacman-right"] = SpriteAnimation{
            getSprites("full_pacman", "pacman_right_little_open", "pacman_right_big_open"),
            false, 2};
    m_spriteAnimations["pacman-dying"] = SpriteAnimation{
            getSprites("pacman_dying_1", "pacman_dying_2", "pacman_dying_3",
                       "pacman_dying_4", "pacman_dying_5", "pacman_dying_6",
                       "pacman_dying_7", "pacman_dying_8", "pacman_dying_9",
                       "pacman_dying_10"), true, 6, false};

    // Ghosts
    initGhostAnimations("blinky");
    initGhostAnimations("clyde");
    initGhostAnimations("inky");
    initGhostAnimations("pinky");

    // Board
    m_spriteAnimations["bonus"] = SpriteAnimation{
            getSprites("bonus", "nothing"), false, 15
    };

    std::cout << "Successfully created " << m_spriteAnimations.size()
              << " sprite animations!" << std::endl;
}

std::optional<SpriteAnimation>
SpriteHandler::getSpriteAnimation(std::string_view name) noexcept
{
    if (auto it = m_spriteAnimations.find(std::string{name}); it != std::end(
            m_spriteAnimations))
        return std::make_optional(it->second);
    else
        return std::nullopt;
}

SpriteHandler::SpriteHandler(std::string_view path) noexcept
{
    importSprites(path);

    // Nothing sprite is a utility sprite that is used in animations to display "nothing"
    m_sprites.emplace_back("nothing");

    // Handle animation init
    initAnimations();
    initStructs();
}

void SpriteHandler::initStructs() noexcept
{
    // Pacman
    m_pacmanAnimations = {
            m_spriteAnimations["pacman-up"],
            m_spriteAnimations["pacman-down"],
            m_spriteAnimations["pacman-left"],
            m_spriteAnimations["pacman-right"],
            m_spriteAnimations["pacman-dying"],
    };

    // Ghosts
    m_blinkyAnimations = {
            m_spriteAnimations["blinky-up"],
            m_spriteAnimations["blinky-down"],
            m_spriteAnimations["blinky-left"],
            m_spriteAnimations["blinky-right"],
    };
    m_pinkyAnimations = {
            m_spriteAnimations["pinky-up"],
            m_spriteAnimations["pinky-down"],
            m_spriteAnimations["pinky-left"],
            m_spriteAnimations["pinky-right"],
    };
    m_inkyAnimations = {
            m_spriteAnimations["inky-up"],
            m_spriteAnimations["inky-down"],
            m_spriteAnimations["inky-left"],
            m_spriteAnimations["inky-right"],
    };
    m_clydeAnimations = {
            m_spriteAnimations["clyde-up"],
            m_spriteAnimations["clyde-down"],
            m_spriteAnimations["clyde-left"],
            m_spriteAnimations["clyde-right"],
    };

    // Board
    m_boardResources = {
            m_spriteAnimations["bonus"],
            getSprite("point").value(),
            getSprite("board_empty").value()
    };

    // Text
    m_textResources = {};
    const std::string str = "abcdefghijklmnopqrstuvwxy0123456789-/!'>@\"";
    std::for_each(str.cbegin(), str.cend(), [this](const char p_char){
        auto sprite = getSprite(std::string{p_char});
        if(!sprite) return;
        m_textResources.alphabetSprites[p_char] = sprite.value();
    });

    m_textResources.nothingSprite = getSprite("nothing").value();
}

void SpriteHandler::initGhostAnimations(const std::string& name) noexcept
{
    m_spriteAnimations[name + "-down"] = SpriteAnimation{
            getSprites(name + "_down_1", name + "_down_2"),
            false, 3};
    m_spriteAnimations[name + "-up"] = SpriteAnimation{
            getSprites(name + "_up_1", name + "_up_2"), false,
            3};
    m_spriteAnimations[name + "-left"] = SpriteAnimation{
            getSprites(name + "_left_1", name + "_left_2"),
            false, 3};
    m_spriteAnimations[name + "-right"] = SpriteAnimation{
            getSprites(name + "_right_1", name + "_right_2"),
            false, 3};
}
