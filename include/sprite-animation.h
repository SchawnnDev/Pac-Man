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
    //int m_changeTicks;
public:

    explicit SpriteAnimation(std::vector<Sprite> &&sprites);

    ~SpriteAnimation() = default;

    virtual void start();
    virtual void stop();
    /**
     * @return Sprite to display
     */
    virtual std::optional<Sprite> display() = 0;

    [[nodiscard]] std::span<const Sprite> sprites() const { return std::span<const Sprite>{m_sprites}; }

    [[nodiscard]] bool activated() const { return m_activated; }
    bool &activated() { return m_activated; }

    [[nodiscard]] bool freeze() const { return m_freeze; }
    bool &freeze() { return m_freeze; }

   // int const &changeTicks() const { return m_changeTicks; };

   // int &changeTicks() { return m_changeTicks; };
};

using SpriteAnimationPtr = std::shared_ptr<SpriteAnimation>;