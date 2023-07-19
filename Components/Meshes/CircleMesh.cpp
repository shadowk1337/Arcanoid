#include "CircleMesh.h"
#include "../../Entities/Scene.h"

void CircleMesh::Move(const Point& offset) {
    m_origin += offset;
}

void CircleMesh::Draw(Frame frame) {
    int row = 0;
    int row_min = 0;
    int row_max = 0;
    int col_min = 0;
    int col_max = 0;
    Point p = {};

    int steps = static_cast<int>(m_radius / m_precision);

    for (int k = 0; k < steps; k++) {
        float x = m_precision * k;
        float y = std::sqrt(m_radius * m_radius - x * x);

        p = m_origin + Point{x, y} + m_radius;
        Scene::RemapPoint(p, row_min, col_min);
        p = m_origin + Point{-x, y} + m_radius;
        Scene::RemapPoint(p, row_max, col_max);

        for (int j = col_max; j <= col_min; j++) {
            frame[row_max][j] = m_color;
        }

        p = m_origin + Point{x, -y} + m_radius;
        Scene::RemapPoint(p, row_min, col_min);
        p = m_origin + Point{-x, -y} + m_radius;
        Scene::RemapPoint(p, row_max, col_max);

        for (int j = col_max; j <= col_min; j++) {
            frame[row_max][j] = m_color;
        }
    }
}
