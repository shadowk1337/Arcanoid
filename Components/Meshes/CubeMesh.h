#pragma once

#include "Mesh.h"
#include "../Component.h"
#include "../../Misc/Scrap.h"

#include <array>

class CubeMesh : public Mesh {
public:
    explicit CubeMesh(
            const std::shared_ptr<Entity>& parent,
            float width,
            float height,
            Color color,
            Point origin = {}
    ) : Mesh(parent)
            , m_width(width)
            , m_height(height)
            , m_color(color)
            , m_origin(origin) {

    }

    void Move(const Point& offset) override;

    void Draw(Frame frame) override;

    const Point& GetOrigin() const { return m_origin; }

    float GetWidth() const { return m_width; }

    float GetHeight() const { return m_height; }

    std::array<Vector, 4> GetSides() const {
        // TODO: Optimize if required (cache e.g.) or check collision without vector common case
        return {
                Vector{
                        m_origin,
                        {m_origin.x + m_width, m_origin.y}
                },
                Vector{
                        {m_origin.x + m_width, m_origin.y + m_height},
                        {m_origin.x,           m_origin.y + m_height}
                },
                Vector{
                        {m_origin.x + m_width, m_origin.y},
                        {m_origin.x + m_width, m_origin.y + m_height}
                },
                Vector{
                        {m_origin.x, m_origin.y + m_height},
                        m_origin
                },
        };
    }

private:
    float m_width = {};
    float m_height = {};
    Point m_origin = {};
    Color m_color = {};
};
