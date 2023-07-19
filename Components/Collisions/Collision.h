#pragma once

#include "../Component.h"
#include "../Meshes/Mesh.h"

#include <functional>
#include <optional>

class Collision : public Component {
public:
    explicit Collision(
            const std::shared_ptr<Entity>& parent,
            const std::shared_ptr<Mesh>& mesh)
            : Component(parent)
            , m_mesh(mesh) {

    }

    virtual std::optional<Vector> Hit(std::shared_ptr<Collision> other) = 0;

    template<class T>
    std::shared_ptr<T> GetMesh() const { return std::dynamic_pointer_cast<T>(m_mesh); }

private:
    std::shared_ptr<Mesh> m_mesh = {};
};
