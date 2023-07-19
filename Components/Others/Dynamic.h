#pragma once

#include <functional>
#include "../Component.h"

class Dynamic : public Component {
public:
    explicit Dynamic(const std::shared_ptr<Entity>& parent) : Component(parent) {}

    virtual void Move(float dt);
};

using DynamicStrategy = std::function<void(float dt)>;

class ConfigurableDynamic : public Dynamic {
public:
    ConfigurableDynamic(
            const std::shared_ptr<Entity>& parent,
            DynamicStrategy&& strategy)
            : Dynamic(parent)
            , m_dynamicStrategy(strategy) {

    }

    void Move(float dt) final { m_dynamicStrategy(dt); }

private:
    DynamicStrategy m_dynamicStrategy = {};
};