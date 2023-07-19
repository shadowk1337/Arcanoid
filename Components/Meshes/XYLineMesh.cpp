#include "XYLineMesh.h"
#include "../../Entities/Scene.h"

XYLineMesh::XYLineMesh(
        const std::shared_ptr<Entity>& parent,
        const Point& start,
        const Point& end,
        Color color)
        : Mesh(parent)
        , m_start(start)
        , m_end(end)
        , m_color(color) {

}

XYLineMesh::XYLineMesh(
        const std::shared_ptr<Entity>& parent,
        Point&& start,
        Point&& end,
        Color color)
        : Mesh(parent)
        , m_start(start)
        , m_end(end)
        , m_color(color) {

}

void XYLineMesh::Move(const Point& offset) {
    m_start += offset;
    m_end += offset;
}

void XYLineMesh::DrawVertical(Frame frame, int column, int row0, int row1) const {
    auto start = std::min(row0, row1);
    auto end = std::max(row0, row1);
    for (int i = start; i <= end; i++) {
        frame[i][column] = m_color;
    }
}

void XYLineMesh::DrawHorizontal(Frame frame, int row, int column0, int column1) const {
    auto start = std::min(column0, column1);
    auto end = std::max(column0, column1);
    for (int j = start; j <= end; j++) {
        frame[row][j] = m_color;
    }
}

void XYLineMesh::Draw(Frame frame) {
    if (!IsHorizontal() && !IsVertical()) {
        throw std::runtime_error("Can only draw horizontal or vertical line");
    }

    int start_col = {};
    int end_col = {};
    int start_row = {};
    int end_row = {};

    Scene::RemapPoint(m_start, start_row, start_col);
    Scene::RemapPoint(m_end, end_row, end_col);

    // TODO: Check in scene and get nearest valid row/col for start/end

    if (IsVertical()) {
        DrawVertical(frame, start_col, start_row, end_row);
    }

    if (IsHorizontal()) {
        DrawHorizontal(frame, start_row, start_col, end_col);
    }
}

bool XYLineMesh::IsHorizontal() const { return m_start.y == m_end.y; }

bool XYLineMesh::IsVertical() const { return m_start.x == m_end.x; }
