#include "Bonus.h"
#include "../Components/Meshes/CubeMesh.h"
#include "../Components/Collisions/Collision.h"
#include "../Components/Collisions/CubeCollision.h"
#include "../Components/Others/Dynamic.h"
#include "Carriage.h"
#include "Block.h"
#include "Scene.h"

void Bonus::Construct() {
    auto mesh = BindComponent<Mesh, CubeMesh>(m_size, m_size, m_color);
    BindComponent<Collision, CubeCollision>(mesh);
    auto movable = BindComponent<Movable>();

    // TODO: make base class for dynamic object(?)
    BindComponent<Dynamic, ConfigurableDynamic>([this, movable, mesh](auto dt) {
        auto offset = m_direction * dt * m_velocity;
        if (!offset) return; // TODO: compare with epsilon
        movable->Move(offset, /*CheckCollision*/ true);
    });
}

bool Bonus::OnHit(std::shared_ptr<Entity> other, std::shared_ptr<Mesh> mesh, const Vector& edge) {
    if (std::dynamic_pointer_cast<Carriage>(other)) {
        if (auto parent = GetParent().lock()) {
            auto scene = std::dynamic_pointer_cast<Scene>(parent);
            auto entities = parent->GetEntities();
            size_t killed = 0;
            while (killed != m_killCount) {
                auto entity = SelectRandom(entities.begin(), entities.end());
                if (entity == std::end(entities)) {
                    return true;
                }
                if (auto block = std::dynamic_pointer_cast<Block>(*entity)) {
                    if (block->IsKilled()) {
                        continue;
                    }
                    scene->KillBlock(block, false);
                    killed++;
                }
            }
        }
        ScheduleKill();
        return true;
    } else if (std::dynamic_pointer_cast<Ball>(other)) {
        return false;
    } else if (std::dynamic_pointer_cast<KillZone>(other)) {
        ScheduleKill();
        return true;
    }

    return false;
}
