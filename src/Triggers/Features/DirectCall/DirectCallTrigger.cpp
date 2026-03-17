//
// Created by Ahmed Mustafa on 7/10/2025.
//

#include "DirectCallTrigger.h"

#include "../../../Application.h"

namespace SPI {

    DirectCallTrigger::DirectCallTrigger(Application* context) : ITrigger(context) {
        context->GetEngineEvents()->travelEvent.Subscribe(([this](const std::shared_ptr<unsigned int>& _) {
            OnTravel();
        }));

        this->type = TRIGGER_TYPE::DIRECT_CALL;
    }

    bool DirectCallTrigger::IsActive() {
        if (context == nullptr) {
            return false;
        }

        if (!isCalled) {
            isCalled = true;
            return true;
        }

        return false;
    }

    void DirectCallTrigger::OnTravel() {
        isCalled = false;
    }

} // SPI