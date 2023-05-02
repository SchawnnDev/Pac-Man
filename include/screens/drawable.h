#pragma once

#include <SDL_render.h>

namespace pacman {

    /**
     * Display root class used by all classes that needs to draw something to screen
     */
    class Drawable {
        bool m_activated;
    public:

        Drawable() : m_activated{true} {}

        explicit Drawable(bool p_activated) : m_activated{p_activated} {}

        ~Drawable() = default;

        /**
         * @return Activate/deactivate this element to be drawn to screen
         */
        [[nodiscard]] bool activated() const { return m_activated; }

        /**
         * @return Activate/deactivate this element to be drawn to screen
         */
        bool &activated() { return m_activated; }

        /**
         * Draw something to screen
         * @param p_window_renderer Window renderer
         * @param p_texture Texture to get sprite from
         */
        virtual void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) = 0;

    };

    using DrawablePtr = std::shared_ptr<Drawable>;

}