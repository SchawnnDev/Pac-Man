#pragma once

#include "ghost.h"

class Blinky : public Ghost {
public:
    Blinky() = default;
    ~Blinky();
    void Tick() override;
};