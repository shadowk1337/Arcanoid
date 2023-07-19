#include "CubeCollision.h"
#include "XYLineCollision.h"

std::optional<Vector> CubeCollision::Hit(std::shared_ptr<Collision> other) {
    // naive check all edges

    {
        if (auto collision = std::dynamic_pointer_cast<CubeCollision>(other)) {
            const auto otherVector = other->GetMesh<CubeMesh>()->GetSides();
            for (const auto& myVector: GetMesh<CubeMesh>()->GetSides()) {
                for (const auto& otherSide: otherVector) {
                    if (myVector.IsIntersect(otherSide)) {
                        return otherSide;
                    }
                }
            }
            return std::nullopt;
        }
    }

    {
        if (auto collision = std::dynamic_pointer_cast<XYLineCollision>(other)) {
            const auto otherVector = other->GetMesh<XYLineMesh>()->GetVector();
            for (const auto& mySide: GetMesh<CubeMesh>()->GetSides()) {
                if (mySide.IsIntersect(otherVector)) {
                    return otherVector;
                }
            }
            return std::nullopt;
        }
    }

    return std::nullopt;
}
