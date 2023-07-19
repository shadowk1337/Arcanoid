#pragma once

#include <random>
#include "Entity.h"
#include "../Components/Collisions/CubeCollision.h"
#include "../Components/Others/Dynamic.h"

class Ball : public Entity {
public:
    explicit Ball(float size, float velocity, Color color)
            : m_size(size)
            , m_velocity(velocity)
            , m_color(color) {

    }

    void Construct() override;

    bool OnHit(
            std::shared_ptr<Entity> other,
            std::shared_ptr<Mesh> mesh,
            const Vector& edge) override;

private:
    float m_size = {};
    float m_velocity = {};
    Color m_color = {};
    Point m_direction = {};
};