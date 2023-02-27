#pragma once

#include <memory>
#include <optional>
#include <span>
#include <vector>

#include "sprite.h"

class SpriteAnimation {
    std::vector<Sprite> m_sprites;
    bool m_activated;
    bool m_freeze;
    bool m_stopAfterLastSprite;
    int m_ticksPerSprite;
    int m_ticks;
    int m_spriteCount;
    int m_currentSprite;
public:
    SpriteAnimation() = default;
    explicit SpriteAnimation(std::vector<Sprite> &&p_sprites,bool p_stopAfterLastSprite = false,int p_ticksPerSprite = 1,bool p_activated = true);

    ~SpriteAnimation() = default;

    void start();
    void stop();
    void reset();

    /**
     * @return Sprite to display
     */
    std::optional<Sprite> display();

    [[nodiscard]] std::span<const Sprite> sprites() const { return std::span<const Sprite>{m_sprites}; }

    [[nodiscard]] bool activated() const { return m_activated; }
    bool &activated() { return m_activated; }

    [[nodiscard]] bool freeze() const { return m_freeze; }
    bool &freeze() { return m_freeze; }

   // int const &changeTicks() const { return m_changeTicks; };

   // int &changeTicks() { return m_changeTicks; };
};