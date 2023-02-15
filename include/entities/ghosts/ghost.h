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
    Ghost() : m_ghostMode(GhostMode::Scatter), m_target{} {}
    ~Ghost() override;

    [[nodiscard]] inline EntityType entityType() const override {
        return EntityType::Ghost;
    }

    [[nodiscard]] const GhostMode &ghostMode() const { return m_ghostMode; };
    GhostMode &ghostMode() { return m_ghostMode; };

    void startScatterMode();

    void startChaseMode();

    void startFrightenedMode();

    void startEatenMode();

};