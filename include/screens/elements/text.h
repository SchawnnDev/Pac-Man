#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <SDL_render.h>

#include "sprites/sprite.h"
#include "sprites/sprite-resources-structs.h"
#include "utils/position.h"
#include "screens/drawable.h"

namespace pacman {

    /**
     * @brief Calculates the pixel width of a string given its length, font size and spacing.
     * @param p_strLen The length of the string.
     * @param p_charSize The size of the font in pixels.
     * @param p_spacing The spacing between characters in pixels.
     * @return The pixel width of the string.
     */
    constexpr int strTextSize(int p_strLen, int p_charSize, int p_spacing)
    {
        return p_strLen * p_charSize + std::max(0, p_strLen - 1) * p_spacing;
    }

    /**
     * @brief Calculates the pixel width of a string given its content, font size and spacing.
     * @param p_str The string to calculate the pixel width of.
     * @param p_charSize The size of the font in pixels.
     * @param p_spacing The spacing between characters in pixels.
     * @return The pixel width of the string.
     */
    constexpr int strTextSize(std::string_view p_str, int p_charSize, int p_spacing)
    {
        return strTextSize(p_str.length(), p_charSize, p_spacing);
    }

    /**
     * @class Text
     * @brief A Drawable class that represents a text element.
     */
    class Text : public Drawable {
        std::vector<Sprite> m_sprites;
        std::string m_text;
        TextResources m_textResources;
        int m_spacing;
        int m_size;
        Position m_position;
        SDL_Color m_color;
    public:

        /**
         * @brief Constructor for the Text class.
         * @param p_text The content of the text.
         * @param p_position The position of the text element on the screen.
         * @param p_size The size of the font in pixels.
         * @param p_spacing The spacing between characters in pixels.
         * @param p_textResources The resources used to render the text.
         */
        Text(std::string p_text, Position p_position, int p_size, int p_spacing, TextResources p_textResources)
            : m_text{std::move(p_text)}
            , m_sprites{}
            , m_textResources{p_textResources}
            , m_size{p_size}
            , m_spacing{p_spacing}
            , m_position{p_position}
            , m_color{255,255,255}
        {}

        /**
         * @return The content of the text.
         */
        [[nodiscard]] std::string const& text() const noexcept { return m_text; }

        /**
         * @return A reference to the content of the text.
         */
        std::string &text() noexcept { return m_text; }

        /**
         * @return The spacing between characters in pixels.
         */
        [[nodiscard]] int spacing() const noexcept { return m_spacing; }

       /**
        * @return Reference to the spacing.
        */
        int& spacing() noexcept { return m_spacing; }

        /**
         * @return The size of the font.
         */
        [[nodiscard]] int size() const noexcept { return m_size; }

        /**
         * @return Reference to the size of the font.
         */
        int& size() noexcept { return m_size; }

        /**
         * @return The position of the text.
         */
        [[nodiscard]] Position const& position() const noexcept { return m_position; }

        /**
         * @return Reference to the position of the text.
         */
        Position &position() noexcept { return m_position; }

        /**
         * @return Reference to the color of the text.
         */
        SDL_Color &color() noexcept { return m_color; }

        /**
         * @brief Calculates and returns the total size of the text.
         *
         * @return The total size of the text.
         */
        [[nodiscard]] inline int textSize() const {
            return strTextSize(m_text, m_size, m_spacing);
        }

        /**
         * @brief Draws the text to the specified renderer and texture.
         *
         * @param p_window_renderer The renderer to draw to.
         * @param p_texture The texture to draw to.
         * @override
         */
        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;
    };

    /**
     * @brief A shared pointer to a Text object.
     */
    using TextElement = std::shared_ptr<Text>;

}
