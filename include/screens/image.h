#pragma once

#include <memory>

#include "drawable.h"
#include "sprite.h"
#include "utils/position.h"

namespace pacman {

    class Image : public Drawable {
        Sprite m_sprite;
        Position m_position;
        Position m_size;
    public:

        Image(const Sprite& p_sprite, Position p_position, Position p_size)
            : m_sprite{p_sprite}
            , m_position{p_position}
            , m_size{p_size}
            {}

        Sprite &sprite() { return m_sprite; }

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

    };

    using ImageElement = std::shared_ptr<Image>;

}
