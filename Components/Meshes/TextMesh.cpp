#include "TextMesh.h"
#include "font.h"
#include "../../Entities/Scene.h"

void TextMesh::Move(const Point& offset) {
    m_origin += offset;
}

void TextMesh::Draw(Frame frame) {
    int row = {};
    int col = {};

    Scene::RemapPoint(m_origin, row, col);

    frame_draw_string(frame, m_color, col, row, m_text.c_str());
}