#pragma once

#include "ghost.h"

class Blinky : public Ghost {
public:
    Blinky() = default;
    ~Blinky() override;
    void Tick() override;
};