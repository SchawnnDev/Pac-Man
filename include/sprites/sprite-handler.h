#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <array>
#include "sprite.h"
#include "sprite-animation.h"
#include "sprite-resources-structs.h"

namespace pacman {

    /**
     * @class SpriteHandler
     * @brief Handles loading and accessing game sprites.
     */
    class SpriteHandler {
        std::vector<Sprite> m_sprites;
        std::unordered_map<std::string, SpriteAnimation> m_spriteAnimations{};
        std::unordered_map<char, Sprite> m_alphabetSprites;
        std::unordered_map<int, Sprite> m_scoresSprites;
        std::array<Sprite, 8> m_fruitsSprites;
        // structs
        PacmanAnimations m_pacmanAnimations;
        GhostAnimations m_blinkyAnimations;
        GhostAnimations m_clydeAnimations;
        GhostAnimations m_pinkyAnimations;
        GhostAnimations m_inkyAnimations;
        BoardResources m_boardResources;
        TextResources m_textResources;
        LoadingScreenResources m_loadingScreenResources;
        FooterScreenResources m_footerScreenResources;
        FruitResources m_fruitResources;
    public:

        /**
         * @brief Constructs a SpriteHandler object with the given file path.
         * @param path The file path to load the sprites from.
         */
        explicit SpriteHandler(std::string_view path);

        /**
         * @brief Get a sprite by name.
         *
         * @param name the name of the sprite
         * @return an optional containing the sprite if found, or an empty optional if not
         */
        [[nodiscard]] std::optional<Sprite> getSprite(std::string_view name) const;

        /**
         * @brief Import sprites from a file.
         *
         * @param path the path to the file
         */
        void importSprites(std::string_view path);

        /**
         * Initialize animations.
         */
        void initAnimations();

        /**
         * Initialize structs.
         */
        void initStructs();

        /**
         * Initialize ghost animations by name.
         *
         * @param name the name of the ghost
         */
        void initGhostAnimations(const std::string &name);

        /**
         * Get a sprite animation by name.
         *
         * @param name the name of the animation
         * @return an optional containing the animation if found, or an empty optional if not
         */
        std::optional<SpriteAnimation> getSpriteAnimation(std::string_view name);

        /**
         * @return An instance for pacman animations
         */
        [[nodiscard]] PacmanAnimations const &pacmanAnimations() const { return m_pacmanAnimations; }

        // Ghosts
        /**
         * @return An instance for blinky animations
         */
        [[nodiscard]] GhostAnimations const &blinkyAnimations() const { return m_blinkyAnimations; }

        /**
         * @return An instance for cylde animations
         */
        [[nodiscard]] GhostAnimations const &clydeAnimations() const { return m_clydeAnimations; }

        /**
         * @return An instance for inky animations
         */
        [[nodiscard]] GhostAnimations const &inkyAnimations() const { return m_inkyAnimations; }

        /**
         * @return An instance for pinky animations
         */
        [[nodiscard]] GhostAnimations const &pinkyAnimations() const { return m_pinkyAnimations; }

        /**
         * @return An instance for fruit resources
         */
        [[nodiscard]] FruitResources const& fruitResources() const { return m_fruitResources; }

        // Screens
        /**
         * @return An instance for text resources
         */
        [[nodiscard]] TextResources const &textResources() const { return m_textResources; }

        /**
         * @return An instance for loading screen resources
         */
        [[nodiscard]] LoadingScreenResources const &loadingScreenResources() const { return m_loadingScreenResources; }

        /**
         * @return An instance for footer screen resources
         */
        [[nodiscard]] FooterScreenResources const &footerScreenResources() const { return m_footerScreenResources; }

        // Board
        /**
         * @return An instance for board resources
         */
        [[nodiscard]] BoardResources const &boardResources() const { return m_boardResources; }

        /**
         * @return A map that contains sprites for scores
         */
        [[nodiscard]] std::unordered_map<int, Sprite> const& scoreSprites() const { return m_scoresSprites; }

       /**
        * @brief Returns a vector of sprites with the given names.
        * @tparam Args Variadic template parameter pack for the sprite names. Each parameter must be convertible to std::string_view.
        * @param p_sprites Sprite names.
        * @return A vector of Sprite objects.
        */
        template<typename... Args>
        requires (... && std::convertible_to<Args, std::string_view>)
        [[nodiscard]]
        std::vector<Sprite> getSprites(Args... p_sprites) const {
            std::array<std::string_view, sizeof...(p_sprites)> sprite_names = {{p_sprites...}};

            auto result = std::vector<Sprite>();
            std::transform(std::cbegin(sprite_names), std::cend(sprite_names),
                           std::back_inserter(result), // Write results to vector
                           [this](std::string_view p_spriteName) {
                               auto sprite = getSprite(p_spriteName);
                               if (!sprite) {
                                   std::cout << "Could not find sprite " << p_spriteName << std::endl;
                               }
                               return getSprite(p_spriteName).value_or(getSprite("nothing").value());
                           });
            return result;
        }

    };

}