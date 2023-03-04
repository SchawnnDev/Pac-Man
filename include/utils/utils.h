#pragma once

namespace pacman {

    constexpr int positiveModulo(int i, int n) noexcept {
        return (i % n + n) % n;
    }

}
