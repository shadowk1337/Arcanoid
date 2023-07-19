#pragma once

#include "Entity.h"

class Bonus : public Entity {
public:
    explicit Bonus(float size, float velocity, Color color, size_t killCount)
            : Entity()
            , m_size(size)
            , m_velocity(velocity)
            , m_color(color)
            , m_killCount(killCount) {

    }

    void Construct() override;

    bool OnHit(std::shared_ptr<Entity> other, std::shared_ptr<Mesh> mesh, const Vector &edge) override;

private:
    float m_size = {};
    float m_velocity = {};
    Color m_color = {};
    size_t m_killCount = {};
    Point m_direction = {0.0f, -1.0f};  // always look down
};