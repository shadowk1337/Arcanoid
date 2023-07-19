#pragma once

#include <cstdint>
#include <memory>
#include "../Engine.h"

class Entity;

class Component {
public:
    virtual ~Component() = default;

    explicit Component(const std::shared_ptr<Entity>& parent)
            : m_parent(parent) {}

    const std::weak_ptr<Entity>& GetParent() { return m_parent; }

protected:
    const std::weak_ptr<Entity> m_parent = {};
};
