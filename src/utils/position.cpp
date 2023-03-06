#include "utils/position.h"

using namespace pacman;

std::ostream &pacman::operator<<(std::ostream &p_str, Position const &v) {
    return p_str << "(" << v.x() << ", " << v.y() << ")";
}
