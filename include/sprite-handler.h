#pragma once

#include <string>
#include <vector>
#include <memory>
#include "sprite.h"

class SpriteHandler {
    std::vector<std::shared_ptr<Sprite>> m_sprites;
public:
    SpriteHandler();
    ~SpriteHandler();

    std::shared_ptr<Sprite> getSprite(const std::string& name);

    void importSprites(const std::string& path);
};