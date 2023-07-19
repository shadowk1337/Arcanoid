#include "Wall.h"
#include "../Components/Collisions/XYLineCollision.h"

void Wall::Construct() {
    auto end = (m_isHorizontal) ? Point{m_length, 0.0f} : Point{0.0f, m_length};
    auto mesh = BindComponent<Mesh, XYLineMesh>(Point{}, end, m_color);
    BindComponent<Collision, XYLineCollision>(mesh);
    BindComponent<Movable>();
}
