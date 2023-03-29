#include <iostream>

#include "pugixml.hpp"

#include "sprites/sprite-handler.h"
#include "utils/constants.h"

using namespace pacman;

SpriteHandler::SpriteHandler(std::string_view path) noexcept
        // Nothing sprite is a utility sprite that is used in animations to display "nothing"
        : m_sprites{Sprite{"nothing"}}
        , m_textResources{m_alphabetSprites}
        , m_footerScreenResources{m_fruitsSprites}
        , m_fruitResources{m_fruitsSprites, m_scoresSprites}
{
    importSprites(path);

    // Handle animation init
    initAnimations();
    initStructs();
}

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
            getSprites("full_pacman", "pacman_up_little_open", "pacman_up_big_open"), false, 2};
    m_spriteAnimations["pacman-left"] = SpriteAnimation{
            getSprites("full_pacman", "pacman_left_little_open", "pacman_left_big_open"), false, 2};
    m_spriteAnimations["pacman-right"] = SpriteAnimation{
            getSprites("full_pacman", "pacman_right_little_open", "pacman_right_big_open"), false, 2};
    m_spriteAnimations["pacman-dying"] = SpriteAnimation{
            getSprites("pacman_dying_1", "pacman_dying_2", "pacman_dying_3",
                       "pacman_dying_4", "pacman_dying_5", "pacman_dying_6",
                       "pacman_dying_7", "pacman_dying_8", "pacman_dying_9",
                       "pacman_dying_10"), true, 6};
    m_spriteAnimations["ghost-frightened"] = SpriteAnimation{getSprites("ghost_frightened_1", "ghost_frightened_2"), false, 3};
    m_spriteAnimations["ghost-frightened-end"] = SpriteAnimation{getSprites("ghost_frightened_1", "ghost_frightened_2", "ghost_frightened_end_1", "ghost_frightened_end_2"), false, GHOST_FRIGHTENED_FLASH_DURATION};
    m_spriteAnimations["ghost-eyes-right"] = SpriteAnimation{getSprites("ghost_eyes_right"), false, 0, true, true};
    m_spriteAnimations["ghost-eyes-left"] = SpriteAnimation{getSprites("ghost_eyes_left"), false, 0, true, true};
    m_spriteAnimations["ghost-eyes-up"] = SpriteAnimation{getSprites("ghost_eyes_up"), false, 0, true, true};
    m_spriteAnimations["ghost-eyes-down"] = SpriteAnimation{getSprites("ghost_eyes_down"), false, 0, true, true};

    // Board
    m_spriteAnimations["board"] = SpriteAnimation{getSprites("board_empty"), false, 0, true, true};
    m_spriteAnimations["board-level-end"] = SpriteAnimation{
            getSprites("board_empty", "board_white", "board_empty", "board_white", "board_empty", "board_white",
                       "board_empty", "board_white"), true, 15, true};

    // Ghosts
    initGhostAnimations("blinky");
    initGhostAnimations("clyde");
    initGhostAnimations("inky");
    initGhostAnimations("pinky");

    // Board
    m_spriteAnimations["bonus"] = SpriteAnimation{getSprites("bonus", "nothing"), false, 15};

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

void SpriteHandler::initStructs() noexcept
{
    auto nothing = Sprite{"nothing"};
    // Pacman
    m_pacmanAnimations = {
            m_spriteAnimations["pacman-up"],
            m_spriteAnimations["pacman-down"],
            m_spriteAnimations["pacman-left"],
            m_spriteAnimations["pacman-right"],
            m_spriteAnimations["pacman-dying"]
    };

    // Ghosts
    m_blinkyAnimations = {
            m_spriteAnimations["blinky-up"],
            m_spriteAnimations["blinky-down"],
            m_spriteAnimations["blinky-left"],
            m_spriteAnimations["blinky-right"],
            m_spriteAnimations["ghost-frightened"],
            m_spriteAnimations["ghost-frightened-end"],
            m_spriteAnimations["ghost-eyes-up"],
            m_spriteAnimations["ghost-eyes-down"],
            m_spriteAnimations["ghost-eyes-left"],
            m_spriteAnimations["ghost-eyes-right"]
    };
    m_pinkyAnimations = {
            m_spriteAnimations["pinky-up"],
            m_spriteAnimations["pinky-down"],
            m_spriteAnimations["pinky-left"],
            m_spriteAnimations["pinky-right"],
            m_spriteAnimations["ghost-frightened"],
            m_spriteAnimations["ghost-frightened-end"],
            m_spriteAnimations["ghost-eyes-up"],
            m_spriteAnimations["ghost-eyes-down"],
            m_spriteAnimations["ghost-eyes-left"],
            m_spriteAnimations["ghost-eyes-right"]
    };
    m_inkyAnimations = {
            m_spriteAnimations["inky-up"],
            m_spriteAnimations["inky-down"],
            m_spriteAnimations["inky-left"],
            m_spriteAnimations["inky-right"],
            m_spriteAnimations["ghost-frightened"],
            m_spriteAnimations["ghost-frightened-end"],
            m_spriteAnimations["ghost-eyes-up"],
            m_spriteAnimations["ghost-eyes-down"],
            m_spriteAnimations["ghost-eyes-left"],
            m_spriteAnimations["ghost-eyes-right"]
    };
    m_clydeAnimations = {
            m_spriteAnimations["clyde-up"],
            m_spriteAnimations["clyde-down"],
            m_spriteAnimations["clyde-left"],
            m_spriteAnimations["clyde-right"],
            m_spriteAnimations["ghost-frightened"],
            m_spriteAnimations["ghost-frightened-end"],
            m_spriteAnimations["ghost-eyes-up"],
            m_spriteAnimations["ghost-eyes-down"],
            m_spriteAnimations["ghost-eyes-left"],
            m_spriteAnimations["ghost-eyes-right"]
    };

    // Board
    m_boardResources = {
            m_spriteAnimations["bonus"],
            getSprite("point").value_or(nothing),
            m_spriteAnimations["board"],
            m_spriteAnimations["board-level-end"]
    };

    // Text
    const std::string str = "abcdefghijklmnopqrstuvwxy0123456789-/!'>@.\"";
    std::for_each(str.cbegin(), str.cend(), [this](const char p_char){
        auto sprite = getSprite(std::string{p_char});
        if(!sprite) return;
        m_alphabetSprites.insert({p_char, sprite.value_or(Sprite{"nothing"})});
    });

    // Screens
    m_loadingScreenResources = {
            getSprite("nothing").value_or(nothing),
            getSprite("blinky_right_1").value_or(nothing),
            getSprite("pinky_right_1").value_or(nothing),
            getSprite("inky_right_1").value_or(nothing),
            getSprite("clyde_right_1").value_or(nothing),
            getSprite("point").value_or(nothing),
            getSprite("score_pts").value_or(nothing),
            getSprite("score_10").value_or(nothing),
            getSprite("score_50").value_or(nothing),
            m_spriteAnimations["bonus"]
    };

    m_footerScreenResources.lifeSprite = getSprite("pacman_life").value_or(nothing);
    std::array<std::string, 8> const fruitNames = {"fruit_cherry", "fruit_raspberry", "fruit_orange", "fruit_apple",
                                                   "fruit_medal", "fruit_helmet", "fruit_bell", "fruit_key"};
    for (int i = 0; i < fruitNames.size(); ++i)
        m_fruitsSprites[i] = getSprite(fruitNames[i]).value_or(nothing);

    //
    std::array<int, 14> const scores = {10, 50, 100, 200, 300, 400, 500, 700, 800, 1000, 1600, 2000, 3000, 5000};
    for (int score: scores)
        m_scoresSprites[score] = getSprite(std::string{"score_" + std::to_string(score)}).value_or(nothing);

}

void SpriteHandler::initGhostAnimations(const std::string& name) noexcept
{
    m_spriteAnimations[name + "-down"] = SpriteAnimation{getSprites(name + "_down_1", name + "_down_2"), false, 3};
    m_spriteAnimations[name + "-up"] = SpriteAnimation{getSprites(name + "_up_1", name + "_up_2"), false, 3};
    m_spriteAnimations[name + "-left"] = SpriteAnimation{getSprites(name + "_left_1", name + "_left_2"), false, 3};
    m_spriteAnimations[name + "-right"] = SpriteAnimation{getSprites(name + "_right_1", name + "_right_2"), false, 3};
}
