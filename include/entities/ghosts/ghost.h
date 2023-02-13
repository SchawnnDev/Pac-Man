#pragma once

#include "../entity.h"

enum class GhostMode {
    Scatter,
    Chase,
    Frightened,
    Eaten
};

class Ghost : public Entity {
    GhostMode m_ghostMode;
    Position m_target;
public:
    Ghost() : m_ghostMode(GhostMode::Scatter), m_target({}) {}
    virtual ~Ghost();

    [[nodiscard]] inline EntityType entityType() const override {
        return EntityType::Ghost;
    }

};