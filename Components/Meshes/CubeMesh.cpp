#pragma once

#include "CubeMesh.h"
#include "../../Entities/Scene.h"

void CubeMesh::Move(const Point& offset) {
    m_origin += offset;
}

void CubeMesh::Draw(Frame frame) {
    int lb_row = 0;
    int lb_col = 0;
    int tb_row = 0;
    int tb_col = 0;

    auto tbCorner = m_origin + Point{m_width, m_height};

    Scene::RemapPoint(m_origin, lb_row, lb_col);
    Scene::RemapPoint(tbCorner, tb_row, tb_col);

    auto start_row = std::min(lb_row, tb_row);
    auto end_row = std::max(lb_row, tb_row);
    auto start_col = std::min(lb_col, tb_col);
    auto end_col = std::max(lb_col, tb_col);

    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_col; j < end_col; j++) {
            frame[i][j] = m_color;
        }
    }
}
