//
// Created by Ahmed Mustafa on 4/21/2025.
//

#ifndef ENGINESTATIONEDRUNSTATE_H
#define ENGINESTATIONEDRUNSTATE_H

#include "EngineStateBase.h"
#include "../Managers/MediaBinder.h"
#include "../Managers/TimeService.h"

namespace SPI {
    class EngineStationedRunState final : public EngineStateBase {
    public:
        ~EngineStationedRunState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering running station state." << std::endl;
        }

        void OnUpdate(Application& app, const float deltaTime) override {
            app.GetTimeService()->StepTime(deltaTime);

            if (app.GetCurrentThread() != -1)
                app.TranslateState(EngineState::FORWARDING);
        }
    };
}

#endif //ENGINESTATIONEDRUNSTATE_H
