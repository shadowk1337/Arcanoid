#pragma once

#include "Entity.h"

class Wall : public Entity {
public:
    Wall(float length, bool isHorizontal, Color color)
            : Entity()
            , m_length(length)
            , m_isHorizontal(isHorizontal)
            , m_color(color) {

    }

    void Construct() override;

private:
    float m_length = {};
    bool m_isHorizontal = {};
    Color m_color = {};
};