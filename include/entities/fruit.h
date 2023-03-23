#pragma once

#include "entity.h"

namespace pacman {

    class Fruit : public Entity {
        FruitResources m_fruitResources;
        int m_ticks;
        bool m_score;
    public:

        explicit Fruit(Board const& p_board, FruitResources p_fruitResources);

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

        static constexpr auto getFruitByLevel(int p_level)
        {
            auto const idx = (p_level >= FRUITS_REGISTERED ? FRUITS_REGISTERED : p_level) - 1;
            return FRUITS_LEVELS[idx];
        }

        void tick() noexcept override;

        void changeAnimation() noexcept override;

        void reset() noexcept override;

        void display(int p_level);

        void eat(int p_score);

        inline EntityType entityType() const noexcept override
        { return EntityType::Fruit; }
    };

}