#pragma once

namespace pacman {

    /**
     * Calculates the positive modulo
     * @param i
     * @param n
     * @return i modulo n
     */
    constexpr int positiveModulo(int i, int n) noexcept {
        return (i % n + n) % n;
    }

}
