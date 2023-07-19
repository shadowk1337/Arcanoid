#include "Ball.h"
#include "Block.h"
#include "Carriage.h"
#include "KillZone.h"
#include "../Components/Meshes/CircleMesh.h"
#include "Scene.h"

void Ball::Construct() {
    m_direction = Point::Random(-1.0f, 1.0f, 0.1f, 1.0f).Normalize();
//        m_direction = Point{1.0f, 0.0f};
//        m_direction = Point{0.0f, 1.0f};

    auto movable = BindComponent<Movable>();

#if defined(CIRCLE_BALL)
    BindComponent<Mesh, CircleMesh>(m_size / 2.0f, m_color);
    auto mesh = BindComponent<CubeMesh>(m_size, m_size, 0x0000'0000);
#elif defined(SQUARE_BALL)
    auto mesh = BindComponent<Mesh, CubeMesh>(m_size, m_size, m_color);
#else
    error "CIRCLE_BALL or SQUARE_BALL should be selected in Scrap.h"
#endif

    BindComponent<Collision, CubeCollision>(mesh);

    BindComponent<Dynamic, ConfigurableDynamic>([this, movable, mesh](auto dt) {
        auto offset = m_direction * dt * m_velocity;
        if (!offset) return; // TODO: compare with epsilon
        movable->Move(offset, /*CheckCollision*/ true);
    });
}

bool Ball::OnHit(
        std::shared_ptr<Entity> other,
        std::shared_ptr<Mesh> mesh,
        const Vector& edge) {
    if (!edge.IsHorizontal() && !edge.IsVertical())
        throw std::runtime_error("Unsupported collision type :(");

    if (std::dynamic_pointer_cast<Carriage>(other)) {
        m_direction.SimpleReflect(edge.IsHorizontal());
        return true;
    } else if (std::dynamic_pointer_cast<Block>(other)) {
#if !defined(BALL_CAN_REFLECT_SIDE_EDGE)
        m_direction.SimpleReflect(true);
#else
        m_direction.SimpleReflect(!edge.IsHorizontal());
#endif
        m_velocity += 1.0f;
        if (auto parent = GetParent().lock()) {
            std::dynamic_pointer_cast<Scene>(parent)->KillBlock(std::dynamic_pointer_cast<Block>(other), true);
        }
        return true;
    } else if (std::dynamic_pointer_cast<KillZone>(other)) {
        ScheduleKill();
        return true;
    } else if (std::dynamic_pointer_cast<Wall>(other)) {
        m_direction.SimpleReflect(edge.IsHorizontal());
        return true;
    }
    return false;
}
