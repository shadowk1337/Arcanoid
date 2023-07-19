#pragma once

#include "../../Misc/Geometry.h"
#include "../../Misc/Scrap.h"
#include "Mesh.h"

#include <algorithm>

class XYLineMesh : public Mesh {
public:
    XYLineMesh(
            const std::shared_ptr<Entity>& parent,
            const Point& start,
            const Point& end,
            Color color);

    XYLineMesh(
            const std::shared_ptr<Entity>& parent,
            Point&& start,
            Point&& end,
            Color color);

    void Move(const Point& offset) override;

    void Draw(Frame screen) override;

    bool IsHorizontal() const;

    bool IsVertical() const;

    Point GetStart() const { return m_start; }

    Point GetEnd() const { return m_end; }

    Vector GetVector() const { return {m_start, m_end}; }

private:
    void DrawVertical(Frame frame, int column, int row0, int row1) const;

    void DrawHorizontal(Frame frame, int row, int column0, int column1) const;

    // TODO: Remake with Vector
    Point m_start = {};
    Point m_end = {};

    Color m_color = {};
};
