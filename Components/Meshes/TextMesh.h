#pragma once

#include "Mesh.h"
#include "../../Misc/Scrap.h"

class TextMesh : public Mesh {
public:
    explicit TextMesh(const std::shared_ptr<Entity>& parent, Color color, Point origin = {})
            : Mesh(parent)
            , m_color(color)
            , m_origin(origin) {

    };

    void Move(const Point& offset) override;

    void Draw(Frame screen) override;

    const std::string& GetText() { return m_text; }

    void SetText(const std::string& string) { m_text = string; }

private:
    Color m_color = {};
    Point m_origin = {};
    std::string m_text = {};
};
