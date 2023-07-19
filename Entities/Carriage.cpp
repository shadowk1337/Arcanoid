#include "Carriage.h"
#include "Bonus.h"
#include "Scene.h"

void Carriage::Construct() {
    auto mesh = BindComponent<Mesh, CubeMesh>(m_width, m_height, m_color);
    BindComponent<Collision, CubeCollision>(mesh);

    BindComponent<Controller, ConfigurableController>([this](auto parent, float dt) {
        if (m_ballHit) {
            m_ballHit = false;
            return;
        }

        auto left = is_key_pressed(VK_LEFT);
        auto right = is_key_pressed(VK_RIGHT);
        if (left && m_CanMoveLeft || right && m_CanMoveRight) {
            auto offset = Point{};

            if (left) {
                offset.x -= m_sensitivity * dt;
                m_MoveLeft = true;
                m_CanMoveRight = true;
            } else {
                offset.x += m_sensitivity * dt;
                m_MoveRight = true;
                m_CanMoveLeft = true;
            }

            parent->template GetComponent<Movable>()->Move(offset, true);
        }

        m_MoveLeft = m_MoveRight = false;
    });

    BindComponent<Movable>();
}

bool Carriage::OnHit(std::shared_ptr<Entity> other, std::shared_ptr<Mesh> mesh, const Vector& edge) {
    if (std::dynamic_pointer_cast<Wall>(other)) {
        if (m_MoveLeft) {
            m_CanMoveLeft = false;
        } else if (m_MoveRight) {
            m_CanMoveRight = false;
        }
        return true;
    } else if (std::dynamic_pointer_cast<Ball>(other)) {
        m_ballHit = true;
        return true;
    }

    return false;
}
