#pragma once

#include "sprite.h"
#include <vector>
#include <memory>

class SpriteAnimation {
    std::vector<std::shared_ptr<Sprite>> m_sprites;
    bool m_activated;
    //int m_changeTicks;
public:
    explicit SpriteAnimation(const std::vector<std::shared_ptr<Sprite>> &sprites);

    SpriteAnimation(std::initializer_list<std::string> args);

    ~SpriteAnimation();


    virtual void start();
    virtual void stop();
    /**
     * @return Sprite to display
     */
    virtual std::shared_ptr<Sprite> display() = 0;

    std::vector<std::shared_ptr<Sprite>> const &sprites() const { return m_sprites; };
    std::vector<std::shared_ptr<Sprite>> &sprites() { return m_sprites; };

    bool const& activated() const { return m_activated; };
    bool &activated() { return m_activated; };

   // int const &changeTicks() const { return m_changeTicks; };

   // int &changeTicks() { return m_changeTicks; };
};