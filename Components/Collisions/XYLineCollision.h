#pragma once

#include "Collision.h"
#include "../Component.h"
#include "../Meshes/XYLineMesh.h"
#include <optional>

class XYLineCollision : public Collision {
public:
    explicit XYLineCollision(
            const std::shared_ptr<Entity>& parent,
            const std::shared_ptr<XYLineMesh>& mesh)
            : Collision(parent, mesh) {

    }

    std::optional<Vector> Hit(std::shared_ptr<Collision> other) override;
};

