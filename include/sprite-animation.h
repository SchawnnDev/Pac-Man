#pragma once

#include "sprite.h"
#include <vector>
#include <memory>
#include <optional>

class SpriteAnimation {
    std::vector<Sprite> m_sprites;
    bool m_activated;
    bool m_freeze;
    //int m_changeTicks;
public:
    SpriteAnimation(std::initializer_list<Sprite> args);

    ~SpriteAnimation();


    virtual void start();
    virtual void stop();
    /**
     * @return Sprite to display
     */
    virtual std::optional<Sprite> display() = 0;

    [[nodiscard]] std::vector<Sprite> const &sprites() const { return m_sprites; };
    std::vector<Sprite> &sprites() { return m_sprites; };

    [[nodiscard]] bool const& activated() const { return m_activated; };
    bool &activated() { return m_activated; };

    [[nodiscard]] bool const& freeze() const { return m_freeze; };
    bool &freeze() { return m_freeze; };

   // int const &changeTicks() const { return m_changeTicks; };

   // int &changeTicks() { return m_changeTicks; };
};

using SpriteAnimationPtr = std::shared_ptr<SpriteAnimation>;