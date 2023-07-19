#include "XYLineCollision.h"
#include "CubeCollision.h"

std::optional<Vector> XYLineCollision::Hit(std::shared_ptr<Collision> other) {
    {
        if (auto collision = std::dynamic_pointer_cast<CubeCollision>(other)) {
            // TODO: Check XYLineCollision with CubeCollision
            // TODO: Make function free or member of some of class
            return std::nullopt;
        }
    }

    {
        if (auto collision = std::dynamic_pointer_cast<XYLineCollision>(other)) {
            auto myVector = GetMesh<XYLineMesh>()->GetVector();
            auto otherVector = collision->GetMesh<XYLineMesh>()->GetVector();
            if (myVector.IsIntersect(otherVector)) {
                return otherVector;
            }

            return std::nullopt;
        }
    }

    return std::nullopt;
}
