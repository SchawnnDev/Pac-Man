#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include "sprite.h"
#include "sprite-animation.h"
#include "sprite-animation-structs.h"

class SpriteHandler {
    std::vector<Sprite> m_sprites{};
    std::map<std::string, SpriteAnimationPtr> m_spriteAnimations{};
    PacmanAnimations m_pacmanAnimations;
public:

    SpriteHandler() = default;

    explicit SpriteHandler(const std::string &path);

    ~SpriteHandler();

    std::optional<Sprite> getSprite(const std::string &name);

    void importSprites(const std::string &path);

    void initAnimations();

    std::optional<SpriteAnimationPtr> getSpriteAnimation(const std::string &name);
};