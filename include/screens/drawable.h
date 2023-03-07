#pragma once

#include <SDL_render.h>

namespace pacman {

    class Drawable {
        bool m_activated;
    public:

        Drawable() : m_activated{true} {}

        explicit Drawable(bool p_activated) : m_activated{p_activated} {}

        ~Drawable() = default;

        [[nodiscard]] bool activated() const { return m_activated; }

        bool &activated() { return m_activated; }

        virtual void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept = 0;

    };

}