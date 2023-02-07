#pragma once

#include "entity.h"

class Banana : public Entity
{
public:
    Banana();
    ~Banana() override;

    void Tick() override;
};