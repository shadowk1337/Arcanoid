#pragma once

#include "Entity.h"
#include "Wall.h"

class KillZone : public Wall {
public:
    KillZone(float length, bool isHorizontal, uint32_t color)
            : Wall(length, isHorizontal, color) {}
};