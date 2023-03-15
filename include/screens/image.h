#pragma once

#include <memory>

#include "drawable.h"
#include "sprites/sprite.h"
#include "utils/position.h"

namespace pacman {

    class Image : public Drawable {
        Sprite m_sprite;
        Position m_position;
        Position m_size;
        SDL_Color m_color;
    public:

        Image(const Sprite& p_sprite, Position p_position, Position p_size)
            : m_sprite{p_sprite}
            , m_position{p_position}
            , m_size{p_size}
            , m_color{255,255,255}
        {}

        Sprite &sprite() { return m_sprite; }
        SDL_Color &color() noexcept { return m_color; }

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

    };

    using ImageElement = std::shared_ptr<Image>;

}
