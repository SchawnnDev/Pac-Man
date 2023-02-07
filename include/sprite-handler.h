#pragma once

#include <string>
#include <vector>
#include <memory>
#include "sprite.h"

class SpriteHandler {
    inline static std::vector<std::shared_ptr<Sprite>> m_sprites = {};
public:
    SpriteHandler();

    ~SpriteHandler();

    static std::shared_ptr<Sprite> getSprite(const std::string &name);

    static void importSprites(const std::string &path);
};