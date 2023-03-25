#pragma once

#include <utility>
#include <vector>

#include <SDL_render.h>

#include "sprites/sprite-resources-structs.h"
#include "screens/elements/text.h"

namespace pacman {

    /**
     * @brief The base class for all screens in the game.
     */
    class Screen : public Drawable {
        int m_ticks;
        std::vector<DrawablePtr> m_elements;
        TextResources m_textResources;
    protected:
        const int m_charSize = 20;
        const int m_spacing = 3;
        const int m_winMiddleX = WINDOW_SIZE_WIDTH / 2;
        const int m_winMiddleY = WINDOW_SIZE_HEIGHT / 2;
    public:

        /**
         * @brief Constructs a new Screen object with the given text resources.
         *
         * @param p_textResources The text resources to use for rendering text.
         */
        explicit Screen(TextResources p_textResources)
        : m_ticks{0}, m_elements{}, m_textResources{p_textResources} {};

        ~Screen() = default;

        /**
         * @return int The number of ticks that have occurred since the screen was activated.
         */
        [[nodiscard]] int ticks() const noexcept { return m_ticks; }

        /**
         * @return A reference to the number of ticks that have occurred since the screen was activated.
         */
        int &ticks() noexcept { return m_ticks; }

        /**
         * @brief Calculates the width of a string in pixels.
         *
         * @param p_len The length of the string.
         * @return int The width of the string in pixels.
         */
        [[nodiscard]] constexpr int CALC(int p_len) const {
            return strTextSize(p_len, m_charSize, m_spacing);
        }

        /**
         * @return A span of the Drawable objects that are drawn on the screen.
         */
        [[nodiscard]] std::span<const DrawablePtr> elements() const { return std::span{m_elements}; }

        /**
         * @return The text resources used for rendering text.
         */
        [[nodiscard]] TextResources const& textResources() const { return m_textResources; }

        /**
         * @brief Adds a Drawable object to the list of objects that are drawn on the screen.
         * @param p_element The Drawable object to add.
         */
        inline void addElement(const DrawablePtr& p_element) {
            m_elements.push_back(p_element);
        }

        /**
         * @brief Adds a span of Drawable objects to the list of objects that are drawn on the screen.
         * @param p_elements The span of Drawable objects to add.
         */
        inline void addElements(std::span<const DrawablePtr> p_elements)
        {
            m_elements.insert(m_elements.end(), p_elements.begin(), p_elements.end());
        }

        /**
         * @brief Advance the screen by one tick.
         *
         * This function should be implemented by derived classes to update the state
         * of the screen by one tick. The exact behavior of the tick function is
         * specific to the particular screen.
         */
        virtual void tick() noexcept = 0;

        /**
         * @brief Reset the screen to its initial state.
         *
         * This function should be implemented by derived classes to reset the state of
         * the screen to its initial state. The exact behavior of the reset function
         * is specific to the particular screen.
         */
        virtual void reset() noexcept = 0;

        /**
         * @brief Draw the screen.
         *
         * This function draws the screen by calling the draw function of each element
         * contained in the screen. The screen is drawn on the given SDL renderer using
         * the given SDL texture.
         *
         * @param p_window_renderer The SDL renderer on which to draw the screen.
         * @param p_texture The SDL texture to use for rendering.
         * @override
         */
        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

    };

}