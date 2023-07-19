#include "Controller.h"
#include "../../Entities/Scene.h"

void Controller::ProcessKey(float dt) {
    if (auto parent = m_parent.lock()) {
        for (const auto& it: parent->GetChildren()) {
            if (auto controller = it->GetComponent<Controller>()) {
                controller->ProcessKey(dt);
            }
        }
    }
}
