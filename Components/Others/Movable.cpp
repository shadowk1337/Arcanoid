#include "Movable.h"

#include "../../Entities/Entity.h"
#include "../Collisions/Collision.h"

void Movable::Move(const Point& offset, bool CheckCollision) {
    if (auto myParent = m_parent.lock()) {
        if (auto mesh = myParent->GetComponent<Mesh>()) {
            mesh->Move(offset);

            auto myCollision = myParent->GetComponent<Collision>();

            if (myCollision) {
                auto collisionMesh = myCollision->GetMesh<Mesh>();
                if (collisionMesh != mesh) {
                    collisionMesh->Move(offset);
                }

                if (CheckCollision) {
                    for (const auto& other: myParent->GetEntities()) {
                        if (*other != *myParent) {
                            if (auto otherCollision = other->GetComponent<Collision>()) {
                                if (auto edge = myCollision->Hit(otherCollision)) {
                                    if (myParent->OnHit(other, otherCollision->GetMesh<Mesh>(), edge.value())) {
                                        mesh->Move(-offset);
                                        if (collisionMesh != mesh) {
                                            collisionMesh->Move(-offset);
                                        }
                                        return; // assume only one hit
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
