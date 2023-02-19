#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include "sprite.h"
#include "sprite-animation.h"

class SpriteHandler {
    inline static std::vector<Sprite> m_sprites = {};
    inline static std::map<std::string, SpriteAnimation> m_spriteAnimations = {};
public:
    SpriteHandler();

    ~SpriteHandler();

    static std::optional<Sprite> getSprite(const std::string &name);

    static void importSprites(const std::string &path);

    static void initAnimations();

    static SpriteAnimation getSpriteAnimation(const std::string &name);
};