#include "Entity.h"

std::list<std::shared_ptr<Entity>> Entity::s_Entities = {};

size_t Entity::s_IdGenerator = {};

Entity::~Entity() {
    m_children.clear();
    m_components.clear();
}

bool Entity::OnHit(
        std::shared_ptr<Entity> other,
        std::shared_ptr<Mesh> mesh,
        const Vector& edge) {
    return false;
}

bool Entity::SetParent(std::shared_ptr<Entity> newParent) {
    if (auto parent = m_parent.lock()) {
        if (parent == newParent) {
            return false;
        }
        parent->m_children.remove_if([this](const auto& it) { return *it == *this; });
    }
    newParent->m_children.push_back(shared_from_this());
    m_parent = newParent;
    return true;
}

void Entity::RemoveParent() {
    auto predicate = [this](const auto& it) { return *it == *this; };
    if (auto parent = m_parent.lock()) {
        parent->m_children.remove_if(predicate);
    }
}

void Entity::CleanKilled() {
    s_Entities.remove_if([](const auto& it) {
        if (it->IsKilled()) {
            it->RemoveParent();
            return true;
        }
        return false;
    });
}
