#pragma once

#include "../Components/Component.h"
#include "../Components/Meshes/XYLineMesh.h"
#include "../Components/Others/Movable.h"
#include "../Misc/Geometry.h"

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <list>
#include <memory>

class Entity : public std::enable_shared_from_this<Entity> {
public:
    template<class T, typename... Args>
    static std::shared_ptr<T> Spawn(Args&& ... args) {
        auto entity = std::make_shared<T>(std::forward<Args>(args)...);
        entity->Construct();
        s_Entities.push_back(entity);
        return entity;
    }

    virtual ~Entity();

    template<class T>
    auto GetComponent() const {
        auto found = m_components.find(typeid(T));
        if (found != std::end(m_components)) {
            return std::dynamic_pointer_cast<T>(found->second);
        }
        return std::shared_ptr<T>{};
    }

    template<class T, typename... Args>
    std::shared_ptr<T> SpawnChildEntityAt(Point&& offset, Args&& ... args) {
        auto child = Spawn<T>(args...);
        if (auto movable = child->template GetComponent<Movable>()) {
            movable->Move(offset, /*CheckCollision*/ false);
        }
        auto parent = shared_from_this();
        child->SetParent(parent);
        return child;
    }

    bool SetParent(std::shared_ptr<Entity> newParent);

    virtual void Construct() = 0;

    bool IsKilled() const { return m_isKilled; }

    void ScheduleKill() {
        m_isKilled = true;
    }

    void RemoveParent();

    static void CleanKilled();

    virtual bool OnHit(
            std::shared_ptr<Entity> other,
            std::shared_ptr<Mesh> mesh,
            const Vector& edge);

    bool operator==(const Entity& other) const { return m_id == other.m_id; }

    bool operator!=(const Entity& other) const { return !(*this == other); }

    const auto& GetChildren() const { return m_children; }

    static const auto& GetEntities() { return s_Entities; }

protected:
    Entity() {
        m_id = s_IdGenerator++;
    }

    template<class Subsystem, class Component>
    bool AddComponent(std::shared_ptr<Component> component) {
        static_assert(std::is_base_of_v<Subsystem, Component>);

        if (auto parent = component->GetParent().lock()) {
            if (*parent != *this) {
                return false;
            }
        }

        auto found = m_components.find(typeid(Subsystem));
        if (found != std::end(m_components)) {
            return false;
        }

        m_components[typeid(Subsystem)] = component;
        return true;
    }

    template<class Subsystem, class Component = Subsystem, typename... Args>
    std::shared_ptr<Component> BindComponent(Args&& ... args) {
        static_assert(std::is_base_of_v<Subsystem, Component>);

        auto found = m_components.find(typeid(Subsystem));
        if (found != std::end(m_components)) {
            return nullptr;
        }

        auto component = std::make_shared<Component>(shared_from_this(), std::forward<Args>(args)...);
        m_components[typeid(Subsystem)] = component;
        return component;
    }

    auto GetParent() const { return m_parent; }

private:
    size_t m_id = {};

    bool m_isKilled = false;

    std::weak_ptr<Entity> m_parent = {};

    std::list<std::shared_ptr<Entity>> m_children = {};

    std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components = {};

    static size_t s_IdGenerator;

    static std::list<std::shared_ptr<Entity>> s_Entities;
};
