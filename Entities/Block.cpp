#include "Block.h"
#include "../Components/Meshes/CubeMesh.h"
#include "../Components/Collisions/Collision.h"
#include "../Components/Collisions/CubeCollision.h"

void Block::Construct() {
    auto mesh = BindComponent<Mesh, CubeMesh>(m_size, m_size, m_color);
    BindComponent<Collision, CubeCollision>(mesh);
    BindComponent<Movable>();
}
