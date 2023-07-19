#include "Mesh.h"
#include "../../Entities/Entity.h"

void Mesh::Move(const Point& offset) {
    if (auto parent = m_parent.lock()) {
        for (const auto& it: parent->GetChildren()) {
            if (auto movable = it->GetComponent<Mesh>()) {
                movable->Move(offset);
            }
        }
    }
}

void Mesh::Draw(Frame frame) {
    if (auto parent = m_parent.lock()) {
        for (const auto& it: parent->GetChildren()) {
            if (auto drawable = it->GetComponent<Mesh>()) {
                drawable->Draw(frame);
            }
        }
    }
}
