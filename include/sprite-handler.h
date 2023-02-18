#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "sprite.h"
#include "sprite-animation.h"

class SpriteHandler {
    inline static std::vector<std::shared_ptr<Sprite>> m_sprites = {};
    inline static std::map<std::string, std::shared_ptr<SpriteAnimation>> m_spriteAnimations = {};
public:
    SpriteHandler();

    ~SpriteHandler();

    static std::shared_ptr<Sprite> getSprite(const std::string &name);

    static void importSprites(const std::string &path);

    static void initAnimations();

    static std::shared_ptr<SpriteAnimation> getSpriteAnimation(const std::string &name);
};