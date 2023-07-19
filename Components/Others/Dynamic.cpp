#pragma once

#include "Dynamic.h"
#include "../../Entities/Scene.h"

void Dynamic::Move(float dt) {
    if (auto parent = m_parent.lock()) {
        for (const auto& it: parent->GetChildren()) {
            if (auto dynamic = it->GetComponent<Dynamic>()) {
                dynamic->Move(dt);
            }
        }
    }
}
