#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "sprite.h"

namespace pacman {

    /**
     * @class SpriteAnimation
     * @brief A SpriteAnimation class representing an animation of sprites.
     */
    class SpriteAnimation {
        std::vector<Sprite> m_sprites;
        bool m_activated;
        bool m_freeze;
        bool m_stopAfterLastSprite;
        bool m_singleSprite;
        int m_ticksPerSprite;
        int m_ticks;
        int m_spriteCount;
        int m_currentSprite;
    public:

        SpriteAnimation() : m_activated{true}, m_freeze{false}, m_stopAfterLastSprite{false}, m_singleSprite{false},
                            m_ticks{0}, m_currentSprite{0}, m_spriteCount{0}, m_ticksPerSprite{0}
        {}


        /**
         * @brief Constructor for SpriteAnimation.
         * @param p_sprites - A vector of sprites.
         * @param p_stopAfterLastSprite - Whether the animation should stop after the last sprite.
         * @param p_ticksPerSprite - The number of ticks per sprite.
         * @param p_activated - Whether the animation is activated.
         * @param p_singleSprite - Whether the animation is a single sprite.
         */
        explicit SpriteAnimation(std::vector<Sprite> &&p_sprites, bool p_stopAfterLastSprite = false,
                                 int p_ticksPerSprite = 1, bool p_activated = true, bool p_singleSprite = false);

        ~SpriteAnimation() = default;

        /**
         * @brief Starts the animation.
         */
        void start();

        /**
         * @brief Stops the animation.
         */
        void stop();

        /**
         * @brief Resets the animation.
         */
        void reset();

        /**
         * @brief Displays the current sprite.
         * @return Optional containing the Sprite to display.
         */
        std::optional<Sprite> display();

        /**
         * @return Span of the sprites contained in animation
         */
        [[nodiscard]] auto sprites() const { return m_sprites; }

        /**
         * @return Boolean indicating whether the animation is activated.
         */
        [[nodiscard]] bool activated() const { return m_activated; }

        /**
         * @return Reference to the boolean indicating whether the animation is activated.
         */
        bool &activated() { return m_activated; }

        /**
         * @return Boolean indicating whether the animation is frozen.
         */
        [[nodiscard]] bool freeze() const { return m_freeze; }

        /**
         * @return Reference to the boolean indicating whether the animation is frozen.
         */
        bool &freeze() { return m_freeze; }

        /**
         * @return Boolean indicating whether the animation is a single sprite.
         */
        [[nodiscard]] bool singleSprite() const { return m_singleSprite; }

        /**
         * @return Reference to the boolean indicating whether the animation is a single sprite.
         */
        bool &singleSprite() { return m_singleSprite; }
    };

}
