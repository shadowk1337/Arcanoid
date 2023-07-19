#pragma once

#include "Collision.h"
#include "CubeCollision.h"
#include "../Component.h"
#include "../Meshes/CubeMesh.h"

class CubeCollision : public Collision {
public:
    explicit CubeCollision(
            const std::shared_ptr<Entity>& parent,
            const std::shared_ptr<CubeMesh>& mesh)
            : Collision(parent, mesh) {

    }

    std::optional<Vector> Hit(std::shared_ptr<Collision> other) override;
};

