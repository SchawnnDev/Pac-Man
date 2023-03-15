#include <iostream>
#include "sprites/sprite-animation.h"

using namespace pacman;

SpriteAnimation::SpriteAnimation(std::vector<Sprite> &&p_sprites,
                                 bool p_stopAfterLastSprite,
                                 int p_ticksPerSprite,
                                 bool p_activated)
        : m_sprites{p_sprites}
        , m_freeze{false}
        , m_stopAfterLastSprite{p_stopAfterLastSprite}
        , m_ticksPerSprite{p_ticksPerSprite}
        , m_ticks{0}
        , m_activated{p_activated}
        , m_spriteCount{static_cast<int>(p_sprites.size())}
        , m_currentSprite{0}
{}

std::optional<Sprite> SpriteAnimation::display() {
    if(!activated())
        return std::nullopt;

    if(freeze())
    {
        auto sprite = sprites()[m_currentSprite];
        if(sprite.isNothing()) return std::nullopt;
        return sprite;
    }

    if(m_ticks >= m_ticksPerSprite)
    {

        if (m_currentSprite >= m_spriteCount - 1)
        {
            if(m_stopAfterLastSprite)
            {
                stop();
                return std::nullopt;
            }

            m_currentSprite = 0;
        } else {
            m_currentSprite++;
        }

        m_ticks = 0;

    }

    m_ticks++;

    auto sprite = sprites()[m_currentSprite];
    if(sprite.isNothing()) return std::nullopt;
    return sprite;
}

void SpriteAnimation::start()
{
    m_activated = true;
}

void SpriteAnimation::stop()
{
    m_activated = false;
}

void SpriteAnimation::reset()
{
    m_ticks = 0;
    m_currentSprite = 0;
}
