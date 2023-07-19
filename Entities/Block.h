#pragma once

#include "Entity.h"

class Block : public Entity {
public:
    explicit Block(float size, Color color)
            : m_size(size)
            , m_color(color) {

    }

    void Construct() override;

private:
    float m_size = {};
    Color m_color = {};
};