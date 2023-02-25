#pragma once

#include <SDL_rect.h>
#include <string>

class Sprite {
    SDL_Rect m_rect;
    std::string m_name;

public:
    Sprite() = default;

    explicit Sprite(const std::string& name);
    ~Sprite();

    [[nodiscard]] std::string const &name() const { return m_name; };
    std::string &name() { return m_name; };

    [[nodiscard]] SDL_Rect const &rect() const { return m_rect; };
    SDL_Rect &rect() { return m_rect; };

    /**
     * Used for animations that do not wish to display anything
     * @return Is nothing
     */
    inline bool isNothing() { return m_name == "nothing"; }

};