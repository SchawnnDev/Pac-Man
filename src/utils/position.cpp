#include "utils/position.h"

#include <cmath>

std::ostream &operator<<(std::ostream &p_str, Position const &v) {
    return p_str << "(" << v.m_x << ", " << v.m_y << ")";
}

constexpr int Position::distanceTo(Position p_target) const noexcept {
    auto x = p_target.x() - m_x;
    auto y = p_target.y() - m_y;
    return x * x + y * y;
}
