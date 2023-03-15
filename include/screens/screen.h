#pragma once

#include <SDL_render.h>
#include <utility>
#include <vector>
#include "sprites/sprite-resources-structs.h"
#include "screens/elements/text.h"
namespace pacman {

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
        explicit Screen(TextResources p_textResources)
        : m_ticks{0}, m_elements{}, m_textResources{p_textResources} {};

        ~Screen() = default;

        [[nodiscard]] int ticks() const noexcept { return m_ticks; }

        int &ticks() noexcept { return m_ticks; }

        [[nodiscard]] constexpr int CALC(int p_len) const {
            return strTextSize(p_len, m_charSize, m_spacing);
        }

        [[nodiscard]] std::span<const DrawablePtr> elements() const { return std::span{m_elements}; }

        [[nodiscard]] TextResources const& textResources() const { return m_textResources; }

        inline void addElement(const DrawablePtr& p_element) {
            m_elements.push_back(p_element);
        }

        inline void addElements(std::span<const DrawablePtr> p_elements)
        {
            m_elements.insert(m_elements.end(), p_elements.begin(), p_elements.end());
        }

        virtual void tick() noexcept = 0;

        virtual void reset() noexcept = 0;

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

    };

}