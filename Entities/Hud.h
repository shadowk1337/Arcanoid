#pragma once

#include "Entity.h"
#include "../Components/Meshes/TextMesh.h"

class Hud : public Entity {
public:
    explicit Hud(Color color)
            : Entity()
            , m_color(color) {

    }

    void Construct() override {
        // TODO: Add composite mesh
        BindComponent<Mesh, TextMesh>(m_color);
        BindComponent<Movable>();
    }

    void SetBlockRemain(const std::string& string) {
        std::dynamic_pointer_cast<TextMesh>(GetComponent<Mesh>())->SetText(string);
    }

private:
    Color m_color = {};
};