#pragma once

constexpr int positiveModulo(int i, int n) noexcept {
    return (i % n + n) % n;
}