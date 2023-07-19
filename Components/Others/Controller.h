#pragma once

#include <functional>
#include "../Component.h"

class Controller : public Component {
public:
    explicit Controller(const std::shared_ptr<Entity>& parent) : Component(parent) {}

    virtual void ProcessKey(float dt);
};

using ControllerStrategy = std::function<void(std::shared_ptr<Entity>, float dt)>;

class ConfigurableController : public Controller {
public:
    ConfigurableController(
            const std::shared_ptr<Entity>& parent,
            ControllerStrategy&& strategy)
            : Controller(parent)
            , m_controllerStrategy(std::move(strategy)) {

    }

    void ProcessKey(float dt) final {
        if (auto parent = m_parent.lock()) {
            m_controllerStrategy(parent, dt);
        }
    }

private:
    ControllerStrategy m_controllerStrategy;
};