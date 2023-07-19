#pragma once

#include "../Component.h"
#include "../../Misc/Geometry.h"

using Frame = uint32_t[SCREEN_HEIGHT][SCREEN_WIDTH];

class Mesh : public Component {
public:
    explicit Mesh(const std::shared_ptr<Entity>& parent) : Component(parent) {}

    virtual void Move(const Point& offset);

    virtual void Draw(Frame frame);
};

