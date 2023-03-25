#pragma once

#include <memory>

#include "screens/drawable.h"
#include "sprites/sprite.h"
#include "utils/position.h"

namespace pacman {
    /**
     * @class Image
     * @brief Represents an image that can be drawn on the screen.
     * @extends Drawable
     */
    class Image : public Drawable {
        Sprite m_sprite;
        Position m_position;
        Position m_size;
        SDL_Color m_color;
    public:

        /**
         * @brief Constructs a new Image object.
         * @param p_sprite The sprite to be used to render the image.
         * @param p_position The position of the top-left corner of the image.
         * @param p_size The size of the image.
         */
        Image(const Sprite& p_sprite, Position p_position, Position p_size)
            : m_sprite{p_sprite}
            , m_position{p_position}
            , m_size{p_size}
            , m_color{255,255,255}
        {}

        /**
         * @return A reference to the sprite used to render the image.
         */
        Sprite &sprite() { return m_sprite; }

        /**
          * @return A reference to the color used to render the image.
          */
        SDL_Color &color() noexcept { return m_color; }

        /**
         * @brief Draws the image on the screen.
         * @param p_window_renderer The SDL_Renderer used to render the image.
         * @param p_texture The SDL_Texture used to render the image.
         * @override
         */
        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

    };

    using ImageElement = std::shared_ptr<Image>;

}
