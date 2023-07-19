#pragma once

#include "Mesh.h"
#include "../Component.h"
#include "../../Misc/Scrap.h"

class CircleMesh : public Mesh {
public:
    explicit CircleMesh(
            const std::shared_ptr<Entity>& parent,
            float radius,
            Color color,
            float precision = 0.01f,
            Point origin = {}
    )
            : Mesh(parent)
            , m_radius(radius)
            , m_color(color)
            , m_precision(precision)
            , m_origin(origin) {

    }

    void Move(const Point& offset) override;

    void Draw(Frame frame) override;

private:
    float m_radius = {};
    Color m_color = {};
    float m_precision = {};
    Point m_origin = {};
};
