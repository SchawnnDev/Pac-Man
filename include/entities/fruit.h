#pragma once

#include "entity.h"

namespace pacman {

    class Fruit : public Entity {
        FruitResources m_fruitResources;
        int m_ticks;
        bool m_score;
    public:

        explicit Fruit(Board const& p_board, FruitResources p_fruitResources);

        /**
         * @param p_level Player level
         * @return Get FRUITS_DISPLAYED last fruits according to p_level
         */
        static constexpr auto getFruitsByLevel(int p_level) {
            std::array<int, FRUITS_DISPLAYED> fruits{-1,-1,-1,-1,-1,-1,-1};
            for (int i = 0; i < FRUITS_DISPLAYED; ++i)
            {
                if(i >= p_level) break;
                auto idx = (p_level >= FRUITS_REGISTERED ? FRUITS_REGISTERED : p_level - i) - 1;
                fruits[i] = FRUITS_LEVELS[idx];
            }
            return fruits;
        }

        /**
         * @param p_level Player level
         * @return Fruit for given p_level
         */
        static constexpr auto getFruitByLevel(int p_level)
        {
            auto const idx = (p_level >= FRUITS_REGISTERED ? FRUITS_REGISTERED : p_level) - 1;
            return FRUITS_LEVELS[idx];
        }

        /**
         * @brief Tick logic, handles intern entities logic
         * @override
         */
        void tick() override;

        /**
         * @brief Changes animations according to fruit mode or score mode
         * @override
         */
        void changeAnimation() override;

        /**
         * @brief Reset all variables to default
         * @override
         */
        void reset() override;

        /**
         * @brief Displays fruit for given level (for 10 seconds)
         * @param p_level Current player level
         */
        void display(int p_level);

        /**
         * @brief Eat fruit, shows score for 3 seconds
         * @param p_score Fruit score
         */
        void eat(int p_score);

        /**
         * @return Type of entity
         * @override
         */
        [[nodiscard]] inline EntityType entityType() const override
        { return EntityType::Fruit; }
    };

}