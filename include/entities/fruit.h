#pragma once

#include "entity.h"

namespace pacman {

    class Fruit : public Entity {

    public:
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
    };

}