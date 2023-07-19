#pragma once

#include "../Component.h"
#include "../../Misc/Geometry.h"

class Movable : public Component {
public:
    explicit Movable(const std::shared_ptr<Entity>& parent) : Component(parent) {}

    virtual void Move(const Point& offset, bool CheckCollision);
};

