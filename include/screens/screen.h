#pragma once

#include <SDL_render.h>
#include <utility>
#include <vector>
#include "sprite-resources-structs.h"
#include "text.h"

namespace pacman {

    class Screen : public Drawable {
        int m_ticks;
        std::vector<std::shared_ptr<Drawable>> m_elements;
        TextResources m_textResources;
    protected:
        const int m_winMiddleX = WINDOW_SIZE_WIDTH / 2;
        const int m_winMiddleY = WINDOW_SIZE_HEIGHT / 2;
    public:
        explicit Screen(TextResources p_textResources)
        : m_ticks{0}, m_elements{}, m_textResources{p_textResources} {};

        ~Screen() = default;

        [[nodiscard]] int ticks() const noexcept { return m_ticks; }

        int &ticks() noexcept { return m_ticks; }

        [[nodiscard]] std::span<const std::shared_ptr<Drawable>> elements() const { return std::span{m_elements}; }

        inline void addElement(const std::shared_ptr<Drawable>& p_element) {
            m_elements.push_back(p_element);
        }

        virtual void tick() noexcept = 0;

        virtual void reset() noexcept = 0;

        void draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept override;

    };

}