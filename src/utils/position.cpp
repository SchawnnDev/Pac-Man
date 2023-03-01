#include "utils/position.h"

#include <cmath>

std::ostream &operator<<(std::ostream &p_str, Position const &v) {
    return p_str << "(" << v.m_x << ", " << v.m_y << ")";
}
