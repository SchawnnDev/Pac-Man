#include "utils/position.h"

std::ostream & operator<<(std::ostream & p_str, Position const& v) {
    return p_str << "(" << v.m_x << ", " << v.m_y << ")";
}
