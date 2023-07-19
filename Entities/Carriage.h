#pragma once

#include "Entity.h"
#include "../Components/Others/Controller.h"
#include "../Components/Meshes/CubeMesh.h"
#include "../Components/Collisions/CubeCollision.h"
#include "Ball.h"
#include "Wall.h"

class Carriage : public Entity {
public:
    explicit Carriage(
            float width,
            float height,
            Color color,
            float sensitivity)
            : m_width(width)
            , m_height(height)
            , m_color(color)
            , m_sensitivity(sensitivity) {

    }

    void Construct() override;

    bool OnHit(
            std::shared_ptr<Entity> other,
            std::shared_ptr<Mesh> mesh,
            const Vector& edge) override;

private:
    float m_width = {};
    float m_height = {};
    Color m_color = {};
    float m_sensitivity = {};

    bool m_ballHit = false;

    bool m_MoveRight = false;
    bool m_MoveLeft = false;

    bool m_CanMoveRight = true;
    bool m_CanMoveLeft = true;
};