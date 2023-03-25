#pragma once

#include <SDL_rect.h>
#include <string>

namespace pacman {

    /**
     * @class Sprite
     * @brief The Sprite class represents an image in the game.
     */
    class Sprite {
        SDL_Rect m_rect{};
        std::string m_name;

    public:
        Sprite() = default;

        /**
         * @brief Constructs a Sprite object with a given name.
         * @param name The name of the sprite.
         */
        explicit Sprite(const std::string &name);

        ~Sprite() = default;

        /**
         * @return The name of the sprite.
         */
        [[nodiscard]] std::string const &name() const { return m_name; };

        /**
         * @return A reference to the name of the sprite.
         */
        std::string &name() { return m_name; };

        /**
         * @return The position of the sprite.
         */
        [[nodiscard]] SDL_Rect const &rect() const { return m_rect; };

        /**
         * @return A reference to the position of the sprite.
         */
        SDL_Rect &rect() { return m_rect; };

        /**
         * @brief Used for animations that do not wish to display anything.
         * @return True if the sprite is nothing, false otherwise.
         */
        inline bool isNothing() { return m_name == "nothing"; }

    };

}